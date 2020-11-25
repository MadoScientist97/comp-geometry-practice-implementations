#!/bin/bash
cd $1
X=1;
for i in $(ls -rt); do
  mv "$i" $(printf %05d.%s ${X%.*} ${i##*.})
  let X="$X+1"
done
cd ..
convert -resize 100% -delay 50 -loop 0 pics/*.png circle.gif
rm CurrentCirclePoints.txt
rm CurrentPoint.txt
rm FinalCircle.txt
rm scatter.txt
rm startpts.txt
rm RecCircle.txt
rm points.txt
rm -rf pics