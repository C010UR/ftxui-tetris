# FTXUI Tetris

## Overview

This is a TUI implementation of modern-ish Tetris with SRS, Combo, and no T-Spin bonuses :)

https://github.com/C010UR/ftxui-tetris/assets/95462776/793ea223-a010-4c5c-b056-c72f527ed169

This project is built with
<img src="https://mesonbuild.com/assets/images/meson_logo.png" height="16px">
[Meson](https://mesonbuild.com/). To install meson you can visit their [GitHub page](https://github.com/mesonbuild/meson/tree/master/docs).

## Dependencies

- [FTXUI](https://github.com/ArthurSonzogni/FTXUI)

## Compilation

To compile the project, first you need to build it using

```console
meson setup {{ build directory }}
```

If you want to build for relase, add `--buildtype=release` flag.<br>
You can compile the project using

```console
meson compile -C {{ build directory }}
```

After compilation a program will be stored in `build` directory

## Running

```console
./build/tetris.exe
```

After running the program the main menu should appear that looks like

<img width="360" alt="image" src="https://github.com/C010UR/ftxui-tetris/assets/95462776/ce90c9a4-3884-45f9-a3fc-9eb73fae35ec">
