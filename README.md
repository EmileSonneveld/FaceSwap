# FaceSwap
Swap faces from a picture with a set of faces from choice

This should be good enauf for mac:
```
git clone --recursive https://github.com/EmileSonneveld/FaceSwap
sudo apt-get install libopencv-dev
cd FaceSwap/source
make
./faceswap

```

Build opencv from source
========================
```
# prpbably need to build opencv from source
cd ./opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
# wait some minutes
sudo make install

```

usage
=====
basically:

```
sudo apt-get install inkscape
cd FaceSwap/source
./faceswap --dest=~/faceswap-picture-here.png
```

The file structure is pretty rigid and goes as follow:
- source -- must be current dir
    - faceswap -- executable
    - file-template.xml
    - img-template.xml
    - [source code]
- photo_result -- will cointain the svg's
    - *.svg -- refers to images with relative paths
- haarcascades -- image recongnition data
    - haarcascade_frontalface_alt.xml
    - haarcascade_frontalface_alt2.xml
    - haarcascade_frontalface_alt_tree.xml
    - haarcascade_frontalface_default.xml
    - ...
- photo_heads -- contains the photos's of heads you want to set_rect
    - *.png
- photos -- for the sake of path's in the SVG file it's advised to place your pictures here


Note to self:
Next time, don't use c++. Go for python instead