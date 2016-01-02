######################################################
# Authors: José Pedro Fonseca, 2015                  #
#           University of Porto, Portugal            #    
#                                                    #
#   Script that transforms an image in a suitable    #
#        format for display at the Nokia5110         #
#                                                    #
######################################################

from   scipy import misc
import matplotlib as plt
import numpy as np

# Reads the image file, and resizes it to fit the Nokia5110 screen
imgSrc = misc.imread('sw.svg');
imgSrc = misc.imresize(imgSrc, (48, 84));

# Converts the RGB image to luminance
imgGray = np.dot(imgSrc[...,:3], [0.299, 0.587, 0.144])

# Dithers the image
for y in range(imgGray.shape[0]):
    for x in range(imgGray.shape[1]):
        old = imgGray[y][x]                         # Keep the old pixel value
        imgGray[y][x] = 0 if old < 128 else 255     # Quantization step
        error = old - imgGray[y][x]                 # The quantization error to be spread
        # Distributing the error among the neighbouring pixels
        if (y == 47) :
            if (x == 83) : continue
            else         : imgGray[y][x+1]   = error * (7/16)
        else :
            if (x == 83) :
                imgGray[y+1][x-1] = imgGray[y+1][x-1] + error * (3/16)
                imgGray[y+1][x]   = imgGray[y+1][x]   + error * (5/16)
            
            else :    
                imgGray[y][x+1]   = imgGray[y][x+1]   + error * (7/16)
                imgGray[y+1][x-1] = imgGray[y+1][x-1] + error * (3/16)
                imgGray[y+1][x]   = imgGray[y+1][x]   + error * (5/16)
                imgGray[y+1][x+1] = imgGray[y+1][x+1] + error * (1/16)

# Shows a preview of the picture
#misc.imshow(imgGray)

# Normalizes the values to {0,1}
imgGray = np.int_(imgGray/255)

# Prints the output to a file, clustering the Byte vertically
fout = open('image.txt', 'w')
fout.write('const char IMG[504] = {\n');
for y in range(0, 48, 8) :
    for i in range(0, 84, 1):
        hexVal = imgGray[y][i] + imgGray[y+1][i]*2 + imgGray[y+2][i]*4 + imgGray[y+3][i]*8 + imgGray[y+4][i]*16 + imgGray[y+5][i]*32 + imgGray[y+6][i]*64 + imgGray[y+7][i]*128
        fout.write("0x{0:02X},\n".format(int(hexVal)));

