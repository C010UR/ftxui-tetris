project('mINI', 'cpp',
    version: '0.9.14',
    meson_version: '>=0.49.0',
    default_options: ['cpp_std=c++17'],
)

cpp = meson.get_compiler('cpp')

depinc = include_directories('src/mini')

mINI = declare_dependency(
  include_directories: depinc,
)