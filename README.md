# FTXUI Tetris

## Overview

This is a TUI implementation of modern-ish Tetris with SRS rotation sytem :)

<img width="1280" alt="image" src="https://github.com/C010UR/ftxui-tetris/assets/95462776/fb7acba5-6ab7-4f0b-ab58-b5ebc5eb678e">

https://github.com/C010UR/ftxui-tetris/assets/95462776/b863148f-418e-450b-878f-db82edf6e99c



This project is built with
<img src="https://mesonbuild.com/assets/images/meson_logo.png" height="16px">
[Meson](https://mesonbuild.com/). To install meson you can visit their [GitHub page](https://github.com/mesonbuild/meson/tree/master/docs).

## Dependencies

- [My fork of FTXUI](https://github.com/C010UR/FTXUI)
- [YAML-CPP](https://github.com/jbeder/yaml-cpp)

## Compilation

To compile the project, first you need to build it using

```console
meson setup {{ build directory }}
```

You can compile the project using

```console
meson compile -C {{ build directory }}
```
