#! /usr/bin/env bash

echo An attempt to have an automated setup will start

sudo apt-get install libopencv-dev cmake
#brew install cmake
#brew install opencv

cd source
make
