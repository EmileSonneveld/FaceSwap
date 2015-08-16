# FaceSwap
Swap faces from a picture with a set of faces from choice

usage:
```
sudo apt-get install inkscape
# probably need openCv too:
sudo apt-get install libopencv-dev
cd FaceSwap/source
./faceswap --dest=~/faceswap-picture-here.png
```

Build faceswap from source Linux:
```
#the submodule is only needed when building opencv from source
git clone https://github.com/EmileSonneveld/FaceSwap
sudo apt-get install libopencv-dev
cd FaceSwap/source
cmake .
make
./faceswap
```

Build opencv from source:
```
# be in the faceswap folder
cd ./opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
# wait some minutes
sudo make install

```



The file structure is pretty rigid and goes as follow:
- source -- must execute from here
    - faceswap -- executable
- photos_orig -- for the sake of path's in the SVG file I advised to place your pictures here
- photos_result_png -- the resulting png picture
- photo_result -- will cointain the svg's
    - *.svg -- refers to images with relative paths
- photo_heads -- contains the photos's that will be put on the faces
    - *.png
- haarcascades -- image recongnition data


Note to self:
Next time, don't use c++. Go for python instead