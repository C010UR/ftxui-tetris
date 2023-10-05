project('FTXUI Tetris', 'cpp',
  version : '1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17'
  ]
)

add_global_arguments('-Wno-unused', language : 'cpp')

cmake = import('cmake')
cmake_opts = cmake.subproject_options()
cmake_opts.add_cmake_defines({'CMAKE_POSITION_INDEPENDENT_CODE': true})

incdir = include_directories('include')

ftxui_screen_dep = dependency('ftxui-screen')
ftxui_dom_dep = dependency('ftxui-dom')
ftxui_component_dep = dependency('ftxui-component')

exe = executable('tetris',
  sources : ['src/main.cpp'],
  include_directories: incdir,
  dependencies: [
    ftxui_screen_dep,
    ftxui_dom_dep,
    ftxui_component_dep
  ]
)