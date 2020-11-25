# comp-geometry-practice-implementations.
Taking a Comp-geometry Class in Uni, created this repo to keep my implememtations of what I learn. Maybe add some visualization later down the line, move from C++ to JS/Python to make it fancier in terms of visualization.

Motivation: To git gud. 

I am pretty new to writing technical docs and this is really my first. Which is why I am writing, to get better. Neither the programs nor this readme should be held up to any standard as of now as I am in uni and using this git as a programming diary of sorts. Hopefully both this readme and the programms get better and become more professional overtime.


How to run. All sentences in quotes are bash Commands. Only process for debian based system is provided as of now. 

IMPORTANT: Only coded to run on linux right now. Needs gnuplot and imagemagic to output the final gifs.
1)  Install g++ if not already present (it should be by default). 
      To install it in debian based systems use "sudo apt-get install g++".
      Or instead update and upgrade the default repos and get the lates version.
      "sudo apt-get update"
      "sudo apt-get upgrade"
  
2) Install Imagemagic and gnuplot:
    For gnuplot: "sudo apt-get install gnuplot"
    For Imagemagick it was enough in my case to install the portable version from software manager of the linux distro I was using. Did not want to mess with installing from source as of now as I know sometimes not installing it correctly can create all sorts of problems. And I did not want any more bugs than I already have.
    Personal Note: Imagemagick is pretty sick tho,if you are into image processing or building image processing apps imagemagick can really help you deep dive.
    
3) Test the installation by running their man pages.
    "man gnuplot"
    "man convert" //convert is one of the tools provided by imagemagick and its the only one that I am using.
     If both man pages work great!! 
4) There are 3 files for each Algo/folder. The main code for the algo is the one with .cpp extension. 
    compile the .cpp file, using : "g++ algoFileName.cpp" No extra parameters.
    Finally run the program using "./a.out "{number of points}" ". 
    Number of points is a commandline arguement. Since this is for computational geometry most of the time the input would be in the form of a set of points. Here I am generating a uniformly random set of points everytime (but the same points will be generated for each input number). This allows us to appreciate the complexity difference between two algos. If both are ran using the same number of points in their arguements then both algo would be working for the same input space.
    
5) Program go brrr (this will take time trust me and ignore the error messages) 
I am not yet good with multi threading/process programming in C++ so to avoid synchronization issues used a duct tape measure of putting the main thread to sleep long enough that the other thread (plottin mainly) would be finished.
Reminder to self: This should be the first part of the program that recieve an upgrade.

6) Finally during the program execution quite a few text files and a folder would be created but everything would be deleted and you'll be left with only two files. A png of the final output and a gif that will try to visualize how the algo was working inside.

7)  That's it. Wish me luck on learning things to end up not having to do anything remotely related when I join somewhere. Yay :x.
