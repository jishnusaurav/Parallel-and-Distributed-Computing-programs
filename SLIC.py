# import the necessary packages
from skimageCode.slic import slic, mark_cuda_labels
from skimage.segmentation import mark_boundaries, find_boundaries
from skimage.color import label2rgb
from skimage.util import img_as_float
from skimage import io
import matplotlib.pyplot as plt
import numpy as np
import argparse

def main():
    # construct the argument parser and parse the arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-k", required=True, help="Number of superpixels ")
    ap.add_argument("-i", "--img", required=True, help="Path to the image")
    ap.add_argument("-p", action="store_true",
        help="Run parallel CUDA version (ignores o)")
    ap.add_argument("-o", action="store_true", help="Run SLICO (ignores m)")
    ap.add_argument("-c", action="store_false",
        help="Don't enforce connectivity")
    ap.add_argument("-s", action="store_false",
        help="Run in CSV mode and suppress displaying pictures.\n" + \
        "Column order is: filename, n, k, parallel, m, slico, connectivity, " +
        "iter, t_htod, t_kernal, t_dtoh, t_total")
    ap.add_argument("-m", "--compactness", default=10.0, help="Compactness")
    ap.add_argument("-n", "--iter", default=10, help="Number of iterations")
    ap.add_argument("-b", action="store_true",
        help="Save Hard Boundary Map for Boundary Recall")
    ap.add_argument("-f", help="Output filepath for Boundary Map")
    args = vars(ap.parse_args())

    # print parameters
    if args["s"]:
        print "\nrunning SLIC on %s with k=%s" % (args["img"],  args["k"])
        print "  parallel=%s, compactness=%s, slic_zero=%s" % \
            (args["p"], args["compactness"], args["o"])
        print "  enforce_connectivity=%s, iter=%s" % (args["c"], args["iter"])
        print "  show_img=%s\n" % (args["s"])

    else:
        print "%s, %s, %s, %s, %s, %s, %s," % (args["img"], args["k"],
            args["p"], args["compactness"], args["o"], args["c"], args["iter"]),

    # load the image and convert it to a floating point data type
    image = img_as_float(io.imread(args["img"]))
    # get rid of img_as_float in order to color the image crazy

    # RUN SLIC
    # default parameters for slic():
    #   n_segments=100, compactness=10.0, max_iter=10, spacing=None,
    #   multichannel=True, convert2lab=None, enforce_connectivity=True,
    #   min_size_factor=0.5, max_size_factor=3, slic_zero=False
    segments, centroids_dim = slic(
        image,
        n_segments = int(args["k"]),
        parallel = args["p"],
        slic_zero = args["o"],
        enforce_connectivity = args["c"],
        compactness = float(args["compactness"]),
        max_iter = int(args["iter"]),
        print_csv = not args["s"]
    )

    # run and save boundary map
    if args["b"]:
        # find boundaries, returns a 2D array of integers.
        # 0 for black, 1 for white boundary
        boundary_map = find_boundaries(segments, mode='inner').astype(int)

        # recode 1 to 255 so when the array is saved as an image,
        # the png knows that 1 means white
        for idx, row in enumerate(boundary_map):
            for col, num in enumerate(row):
                if num == 1:
                    boundary_map[idx][col] = 255

        # save image
        io.imsave(args["f"], boundary_map)

    # DISPLAY SEGMENTS
    # optionally color image by superpixel averages with CUDA
    if args["p"]:
        # is currently reflected across y=x line
        # when connectivity is enforced possibly due to np.ascontiguousarray
        image_cuda = image[np.newaxis, ...]
        image_colored_cuda = \
            mark_cuda_labels(image_cuda, centroids_dim, segments)[0]

    # color image by superpixel averages
    image_colored = label2rgb(segments, image, kind = "avg")

    # superimpose superpixels onto image
    image_segmented = mark_boundaries(image, segments, mode='inner')

    # show the output of SLIC
    if(args["s"]):
        # original
        fig = plt.figure("original - %s %s" % (args["img"], image.shape))
        ax = fig.add_subplot(1, 1, 1)
        ax.imshow(image)
        plt.axis("off")

        # mosaic
        fig = plt.figure("mosaic - %s %s %s" %
            (args["img"], image.shape, centroids_dim))
        ax = fig.add_subplot(1, 1, 1)
        ax.imshow(image_segmented)
        plt.axis("off")

        # dyed
        fig = plt.figure("dyed skimage - %s %s %s" %
            (args["img"], image.shape, centroids_dim))
        ax2 = fig.add_subplot(1, 1, 1)
        ax2.imshow(image_colored)
        plt.axis("off")

        # CUDA dyed
        if args["p"]: # and not args["c"]:
            # does not work correctly if connectivity is enforced
            fig = plt.figure("dyed cuda - %s %s %s" %
                (args["img"], image.shape, centroids_dim))
            ax = fig.add_subplot(1, 1, 1)
            ax.imshow(image_colored_cuda)
            plt.axis("off")

        # boundary map
        if args["b"]:
            fig = plt.figure("boundary map - %s %s %s" %
                (args["img"], image.shape, centroids_dim))
            ax3 = fig.add_subplot(1, 1, 1)
            ax3.imshow(boundary_map, cmap="gray")
            plt.axis("off")

        # show the plots
        plt.show()

if __name__=="__main__":
    main()
