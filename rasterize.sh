#! /usr/bin/env bash

echo Converting will start

#on-liner that will asure that we execute in the directory where the file is
cd $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

export PATH=/Applications/Inkscape.app/Contents/Resources/bin/:$PATH

DEST=$PWD"/photo_result_png/pic_example.png"

if [ $# -eq 0 ]; then
	echo "using deafoult path"
else
	echo "Overwriting path with argument 1 "$1
	DEST=$1
fi

echo "Dest:" $DEST

inkscape $PWD/photo_result/pic_example.svg --export-png=$DEST
