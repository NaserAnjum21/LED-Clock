# Description
An iGraphics project to display current time ticking on graphical interface. It's a very simple project but my first project with any kind of graphical interface. So, it will always be a special one.

## Instruction

To run the program, do the following

```
Open the .cbp file in Codeblocks IDE
Build and Run project
```

or you can do

```
Go to bin/debug and run .exe file
```

## Note

iGraphics is an wrapper for OpenGL library in 2D. Most of the neccessary header files are put in the project folder but you might face errors or crashes and might need to make sure of few additional things related to compiler directory.

1. check if glut.h is present in compiler directory, i.e in MinGW/include/GL
2. check if libglut32.a is is present in MinGW/lib
