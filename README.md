# FaceSwap
Swap faces from a picture with a set of faces from choice

git clone --recursive https://github.com/EmileSonneveld/FaceSwap
cd FaceSwap

c++ version
===========
sudo apt-get install libopencv-dev
cd source
make

ruby version
================
brew install homebrew/science/opencv
sudo gem install ruby-opencv -- --with-opencv-dir=`brew --prefix opencv`
cd ruby_version
ruby main.rb


This program assumes hardcoded paths:
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

The outputted SVG is viewed best with a browser.
