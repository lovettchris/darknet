![Darknet Logo](http://pjreddie.com/media/files/darknet-black-small.png)

#Darknet#
Darknet is an open source neural network framework written in C and CUDA. It is fast, easy to install, and supports CPU and GPU computation.

For more information see the [Darknet project website](http://pjreddie.com/darknet).

For questions or issues please use the [Google Group](https://groups.google.com/forum/#!forum/darknet).

To build the windows version with opencv support, do this (after installing latest opencv source building it):

````
mkdir windows
cd windows
set OpenCV_DIR=D:\OpenSource\opencv\build
cmake -G "Visual Studio 14 2015 Win64" -D OPENCV=1 ..
cmake --build --config Release
````