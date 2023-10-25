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
mini_dep = dependency('mINI')

executable('tetris',
  sources : [
    'src/main.cpp',
    'src/t_config/t_config.cpp',
    'src/t_config/t_controls.cpp',
    'src/t_config/t_serializer.cpp',
    'src/t_config/t_theme.cpp',
    'src/t_engine/t_renderer.cpp',
    'src/t_game/t_board.cpp',
    'src/t_game/t_hold.cpp',
    'src/t_game/t_next.cpp',
    'src/t_game/t_score.cpp',
    'src/t_game/t_tetromino_factory.cpp',
    'src/t_game/t_tetromino.cpp',
    'src/t_menu/t_menus/t_change_key.cpp',
    'src/t_menu/t_menus/t_controls.cpp',
    'src/t_menu/t_menus/t_game_over.cpp',
    'src/t_menu/t_menus/t_main_menu.cpp',
    'src/t_menu/t_menus/t_options.cpp',
    'src/t_menu/t_menu.cpp',
    'src/t_renderer/t_canvas.cpp',
    'src/t_renderer/t_color.cpp',
    'src/t_renderer/t_data_transformer.cpp',
    'src/t_renderer/t_header.cpp',
    'src/t_renderer/t_key_value.cpp',
  ],
  include_directories: incdir,
  dependencies: [
    ftxui_screen_dep,
    ftxui_dom_dep,
    ftxui_component_dep,
    mini_dep
  ]
)