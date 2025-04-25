project('sfml_game_base', 'cpp',
  version : '1.0',
  default_options : [
    'warning_level=1',
    'cpp_std=c++17',
])

srcs = [
  'srcs/InputManager.cpp',
  'srcs/main.cpp',
]

executable('sfml_game_base',
          srcs,
          build_rpath: '.',
          dependencies : [
              dependency('sfml', static: true),
              dependency('libjson', static: true),
          ],
          include_directories: include_directories('srcs'),
          install : true)

install_subdir('data', install_dir:'.')
