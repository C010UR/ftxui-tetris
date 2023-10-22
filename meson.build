project('FTXUI Tetris', 'cpp',
  version : '1',
  meson_version: '>= 1.2.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17'
  ]
)

add_global_arguments('-Wno-unused', language : 'cpp')

incdir = include_directories('include')

ftxui_screen_dep = dependency('ftxui-5.0.0-screen')
ftxui_dom_dep = dependency('ftxui-5.0.0-dom')
ftxui_component_dep = dependency('ftxui-5.0.0-component')

executable('tetris',
  sources : ['src/main.cpp'],
  include_directories: incdir,
  dependencies: [
    ftxui_screen_dep,
    ftxui_dom_dep,
    ftxui_component_dep
  ]
)