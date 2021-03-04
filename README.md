# ggr2glsl

ggr2glsl is a simple utility to convert GIMP gradient files to GLSL functions.

## Usage

ggr2glsl reads from standard input and writes to standard output.

To convert a gradient called purples.ggr
to a glsl function, with the file name myGradient.glsl, do:

```
./ggr2glsl < purples.ggr > myGradient.glsl
```

The file myGradient.glsl now contains, among some other functions,
`ggr2glsl_color`.

This function takes a floating point value and returns a vec4, the color
in the gradient.

## Download (Windows)
https://github.com/ErikPrantare/ggr2glsl/releases/tag/v0.0.0

## Build (Linux)
```sh
cmake . -Bbuild
cmake --build build
mv build/ggr2glsl .
```

# Example
Following is an example of a gradient, and it being applied to
[Mandelscape](https://github.com/ErikPrantare/Mandelscape):

![ggr](media/ggr.jpeg?raw=true)
![glsl](media/glsl.jpeg?raw=true)
