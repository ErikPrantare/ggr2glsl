#ggr2glsl

This is a simple utility to convert GIMP gradient files to GLSL functions.

#Usage

ggr2glsl reads from standard input and writes to standard output.
Say that you want to convert a gradient called purples.ggr
to a glsl function, with the file name myGradient.glsl.
You would do it like this:

```
./ggr2glsl < purples.ggr > myGradient.glsl
```

The file myGradient.glsl now contains, among some other functions,
`ggr2glsl_color`.
To use this function, simply pass it a floating point number and you will get
the respective gradient color.

#Download (Windows)
tba

#Build (Linux)
```sh
cmake -Bbuild
cmake --build build
mv build/ggr2glsl .
```

#Example
Following is an example of a gradient, and it being applied to
[Mandelscape](https://github.com/ErikPrantare/Mandelscape):

![ggr](media/ggr.jpeg?raw=true)
![glsl](media/glsl.jpeg?raw=true)
