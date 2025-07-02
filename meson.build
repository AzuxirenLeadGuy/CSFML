project(
  'CSFML-custom',
  ['cpp', 'c'],
  meson_version: '>= 1.3.0',
  version: '3.0.1',
  default_options: {'warning_level': '3', 'buildtype': 'release'},
)

proj_inc_dir = include_directories('include')

proj_src_list = [
  # Copy the output of `$ find ./src -type f -name "*.c*" | sed "s/.*/'&',/"`
  './src/CSFML/System/Sleep.cpp',
  './src/CSFML/System/Clock.cpp',
  './src/CSFML/System/Time.cpp',
  './src/CSFML/System/Alloc.cpp',
  './src/CSFML/System/Buffer.cpp',
  './src/CSFML/Window/Mouse.cpp',
  './src/CSFML/Window/VideoMode.cpp',
  './src/CSFML/Window/Joystick.cpp',
  './src/CSFML/Window/Keyboard.cpp',
  './src/CSFML/Window/Touch.cpp',
  './src/CSFML/Window/WindowBase.cpp',
  './src/CSFML/Window/Vulkan.cpp',
  './src/CSFML/Window/Context.cpp',
  './src/CSFML/Window/Cursor.cpp',
  './src/CSFML/Window/Clipboard.cpp',
  './src/CSFML/Window/Window.cpp',
  './src/CSFML/Window/Sensor.cpp',
  './src/CSFML/Main/SFML_Main.cpp',
  './src/CSFML/Graphics/Color.cpp',
  './src/CSFML/Graphics/Transform.cpp',
  './src/CSFML/Graphics/Text.cpp',
  './src/CSFML/Graphics/Transformable.cpp',
  './src/CSFML/Graphics/RenderStates.cpp',
  './src/CSFML/Graphics/ConvexShape.cpp',
  './src/CSFML/Graphics/CircleShape.cpp',
  './src/CSFML/Graphics/View.cpp',
  './src/CSFML/Graphics/Rect.cpp',
  './src/CSFML/Graphics/VertexBuffer.cpp',
  './src/CSFML/Graphics/Shader.cpp',
  './src/CSFML/Graphics/BlendMode.cpp',
  './src/CSFML/Graphics/VertexArray.cpp',
  './src/CSFML/Graphics/Image.cpp',
  './src/CSFML/Graphics/StencilMode.cpp',
  './src/CSFML/Graphics/Texture.cpp',
  './src/CSFML/Graphics/Font.cpp',
  './src/CSFML/Graphics/RectangleShape.cpp',
  './src/CSFML/Graphics/RenderWindow.cpp',
  './src/CSFML/Graphics/Shape.cpp',
  './src/CSFML/Graphics/RenderTexture.cpp',
  './src/CSFML/Graphics/Sprite.cpp',
  './src/CSFML/Audio/SoundBufferRecorder.cpp',
  './src/CSFML/Audio/Listener.cpp',
  './src/CSFML/Audio/SoundBuffer.cpp',
  './src/CSFML/Audio/SoundStream.cpp',
  './src/CSFML/Audio/SoundRecorder.cpp',
  './src/CSFML/Audio/Music.cpp',
  './src/CSFML/Audio/Sound.cpp',
  './src/CSFML/Network/Http.cpp',
  './src/CSFML/Network/TcpListener.cpp',
  './src/CSFML/Network/TcpSocket.cpp',
  './src/CSFML/Network/UdpSocket.cpp',
  './src/CSFML/Network/IpAddress.cpp',
  './src/CSFML/Network/Ftp.cpp',
  './src/CSFML/Network/SocketSelector.cpp',
  './src/CSFML/Network/Packet.cpp',
]

cmake = import('cmake')

shared_lib_opts = cmake.subproject_options()
shared_lib_opts.add_cmake_defines({'BUILD_SHARED_LIBS': '1'})

sfml_subproj_shared = cmake.subproject(
  'sfml',
  options: shared_lib_opts,
)

sfml_subproj_static = cmake.subproject('sfml')

sfml_shared_deps = []
sfml_static_deps = []
sfml_mod_list = ['system', 'window', 'graphics', 'audio', 'network']

foreach mod_name : sfml_mod_list
  full_mod = 'sfml-' + mod_name
  sfml_shared_deps += sfml_subproj_shared.dependency(full_mod)
  sfml_static_deps += sfml_subproj_static.dependency(full_mod)

endforeach

lib_sfml_static = static_library(
  meson.project_name(),
  proj_src_list,
  dependencies: sfml_static_deps,
  install: true,
  include_directories: [proj_inc_dir],
  pic: true,
)

lib_sfml_shared = shared_library(
  meson.project_name(),
  proj_src_list,
  dependencies: sfml_shared_deps,
  install: true,
  include_directories: [proj_inc_dir],
)

test_src_list = [
  # Copy the output of `$ find ./test -type f -name "*.c*" | sed "s/.*/'&',/"`
  './test/System/Vector2.test.cpp',
  './test/System/Clock.test.cpp',
  './test/System/Vector3.test.cpp',
  './test/System/Buffer.test.cpp',
  './test/System/Time.test.cpp',
  './test/System/Sleep.test.cpp',
  './test/Window/Joystick.test.cpp',
  './test/Window/Keyboard.test.cpp',
  './test/Window/Window.test.cpp',
  './test/Window/WindowBase.test.cpp',
  './test/Window/Mouse.test.cpp',
  './test/Window/Sensor.test.cpp',
  './test/Graphics/Shape.test.cpp',
  './test/Graphics/CoordinateType.test.cpp',
  './test/Graphics/PrimitiveType.test.cpp',
  './test/Graphics/StencilMode.test.cpp',
  './test/Graphics/VertexArray.test.cpp',
  './test/Graphics/Transform.test.cpp',
  './test/Graphics/Color.test.cpp',
  './test/Graphics/BlendMode.test.cpp',
  './test/Graphics/Rect.test.cpp',
  './test/Graphics/View.test.cpp',
  './test/Graphics/Image.test.cpp',
  './test/Graphics/RenderStates.test.cpp',
  './test/Audio/SoundChannel.test.cpp',
  './test/Network/Ftp.test.cpp',
  './test/Network/SocketStatus.test.cpp',
  './test/Network/Http.test.cpp',
  './test/Network/IpAddress.test.cpp',
]

catch2_dep = subproject('Catch2').get_variable('catch2_with_main_dep')

foreach test_src : test_src_list
  name = test_src.split('/')[-1].split('.')[0]
  message('Preparing unit test ' + name + ' , at path ' + meson.current_source_dir())
  test(
    name,
    executable(
      name,
      [test_src],
      link_with: [lib_sfml_static],
      include_directories: [proj_inc_dir],
      dependencies: [catch2_dep, sfml_static_deps],
    ),
    workdir: meson.current_source_dir() + '/test',
  )
endforeach

executable(
  'example',
  ['examples/example.c'],
  link_with: [lib_sfml_shared],
  include_directories: [proj_inc_dir],
  link_language: 'c',
)