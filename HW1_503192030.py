# -*- coding: utf-8 -*-
"""HW1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/17wbjRZ1XipPS5B072zPZtfuCxPrVc9Gj
"""

import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
from PIL import ImageFilter
from PIL import ImageOps
from PIL import ImageColor
from PIL import ImageEnhance
import imageio
import cv2

# QUESTION 1

# Getting the image called Sea

img = imageio.imread('sea.jpeg')
img_cvt= cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)
plt.imshow(img_cvt)
plt.title('Sea Image')
plt.show()

"""# Yeni Bölüm"""

#Divide the image to 4 quadrants and keep Q1 as the original image

size1 = img.shape[0]
size2 = img.shape[1]

half1 = int(size1/2)
half2 = int(size2/2)

# Q2 brightness increase

image1 = Image.fromarray(img[0:half1, half2:size2])

br = ImageEnhance.Brightness(image1)
br = br.enhance(1.3)
image1_arr = np.asarray(br)
img[0:half1, half2:size2] = image1_arr

#Q3 contrast increase

image2 = Image.fromarray(img[half1:size1, 0:half2])

cnt = ImageEnhance.Contrast(image2)
cnt = cnt.enhance(1.6)

image2_arr = np.asarray(cnt)

img[half1:size1, 0:half2] = image2_arr

# Q4 histogram equalization

image3 = Image.fromarray(img[half1:size1, half2:size2])

st = ImageOps.equalize(image3)
image3_arr = np.asarray(st)
# Merge Q1 and modified Q2,Q3,Q4 into a single image
img[half1:size1, half2:size2] = image3_arr
plt.title('Sea Image divided to 4 Quadrants')
plt.imshow(img)

#Histograms of Each Quadrant

color = ('b','g','r')
fig=plt.figure(figsize=(12, 10))
fig.add_subplot(4, 1, 1)
for channel,col in enumerate(color):
    histr = cv2.calcHist([img[0:half1, 0:half2]],[channel],None,[256],[0,256])
    plt.plot(histr,color = col)
    plt.xlim([0,256])
plt.title('Histogram Color Scale Quadrant-1')
fig.add_subplot(4, 1, 2)
for channel,col in enumerate(color):
    histr = cv2.calcHist([image1_arr],[channel],None,[256],[0,256])
    plt.plot(histr,color = col)
    plt.xlim([0,256])
plt.title('Histogram Color Scale Quadrant-2')
fig.add_subplot(4, 1, 3)
for channel,col in enumerate(color):
    histr = cv2.calcHist([image2_arr],[channel],None,[256],[0,256])
    plt.plot(histr,color = col)
    plt.xlim([0,256])
plt.title('Histogram Color Scale Quadrant-3')
fig.add_subplot(4, 1, 4)
for channel,col in enumerate(color):
    histr = cv2.calcHist([image3_arr],[channel],None,[256],[0,256])
    plt.plot(histr,color = col)
    plt.xlim([0,256])
plt.title('Histogram Color Scale Quadrant-4')
plt.subplots_adjust(hspace=0.5)
plt.show()

# QUESTION 2

# Getting the image called a

img = imageio.imread('a.png')
img_cvt= cv2.cvtColor(img, cv2.COLOR_RGB2RGBA)
plt.imshow(img_cvt)
plt.title('Image without filter')
plt.show()

#ksize x ksize median filter as ksize = 5
from PIL import Image
im = Image.open('/content/a.png').convert('RGB')

im2 = im.filter(ImageFilter.MedianFilter(size = 5))
plt.imshow(im2)
plt.title('Image with Median Filter')
plt.show()

im = Image.open('/content/a.png').convert('RGBA')
members = [(0,0)] * 25
width, height = im.size
newimg = Image.new("RGB", (width, height), "white")

for i in np.arange(2,width-2):
    for j in np.arange(2,height-2):
        a=0
        for k in np.arange(-2,3):
            for l in np.arange(-2,3):
                members[a] = im.getpixel((int(i+k),int(j+l)))
                a+=1         
        members.sort()
        newimg.putpixel((i,j),(members[13]))
plt.title('Image with 5x5 Median Filter')
fig.add_subplot(1, 1, 1)

plt.imshow(newimg)

# QUESTION 3

#Getting the image called sea

img = imageio.imread('sea.jpeg')
img_cvt= cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)
plt.imshow(img_cvt)
plt.title('Sea Image')
plt.show()

img = img[:,:,0]

fig=plt.figure(figsize=(10, 10))

f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)
magnitude_spectrum = 20*np.log(np.abs(fshift))
fig.add_subplot(2, 2, 1)
plt.title('Spectrum')
plt.imshow(magnitude_spectrum, 'gray')

rows = img.shape[0]
cols = img.shape[1]
crow,ccol = rows//2 , cols//2
fshift[crow-90:crow+90, ccol-90:ccol+90] = 0
f_ishift = np.fft.ifftshift(fshift)
img_back = np.fft.ifft2(f_ishift)
img_back = np.abs(img_back)
fig.add_subplot(2, 2, 2)
plt.title('Components')
plt.imshow(img_back, 'gray')

fig.add_subplot(2, 2, 3)
plt.title('Gray Image')
plt.imshow(img, 'gray')

fig.add_subplot(2, 2, 4)
plt.title('High Frequency Image')
plt.imshow(img-img_back, 'gray')