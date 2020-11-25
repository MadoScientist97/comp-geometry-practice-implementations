#!/bin/bash
cd $1
X=1;
for i in $(ls -rt); do
  mv "$i" $(printf %05d.%s ${X%.*} ${i##*.})
  let X="$X+1"
done
cd ..
convert -resize 100% -delay 20 -loop 0 pics/*.png convexHull.gif
rm -r pics
rm currentLLine.txt
rm currentULine.txt
rm lowerhull.txt
rm upperhull.txt
rm scatter.txt
rm currentpt.txt