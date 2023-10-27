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

## Configuration

Configuration of the project is stored in the `config.yaml` file

```yaml
config:
  easyMode: true # turns on shardow of the tetromino
  level: 1 # level from 1 to 15
  updatesPerSecond: 240 # can help with performance in certain cases
  currentTheme: Autumn Haze # current theme
  storeDelayMs: 500 # ms before tetromino is saved to the board
  softDropDelayMs: 50 # detection rate of the soft drop press
  softDropGravityMsPerRow: 20 # soft drop gravity 
  comboDelayMs: 6000 # combo timeout
  debug: false # debug mode
  themes:
    - name: Default
      mainColorsGradient: # headers gradient
        - "#4cd137"
        - "#4cce3c"
        - "#4ccb41"
        - "#4cc54a"
        - "#4bb85d"
        - "#4bab70"
        - "#42916a"
        - "#387763"
        - "#254f42"
      gameOverColorsGradient: # game over gradient
        - "#e84118"
        - "#d63c1f"
        - "#c43725"
        - "#a02d32"
        - "#57194b"
      mainColor: "#4a9e83"
      gameOverColor: "#57194b"
      valueColor: "#4bb365"
      trueColor: "#4cd137"
      falseColor: "#e84118"
      IColor: "#00a8ff"
      OColor: "#fbc531"
      TColor: "#9c88ff"
      JColor: "#2b2cd5"
      LColor: "#f28325"
      SColor: "#4cd137"
      ZColor: "#e84118"
controls:
  moveLeft: a
  moveRight: d
  rotateLeft: ","
  rotateRight: .
  swapHold: z
  softDrop: s
  hardDrop: " "
  forfeit: t
  retry: r
```
