echo Converting will start

export PATH=/Applications/Inkscape.app/Contents/Resources/bin/:$PATH

inkscape $PWD/photo_result/pic_example.svg --export-png=$PWD/photo_result_png/pic_example.png
