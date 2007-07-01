from glob import glob

destdir = ARGUMENTS.get('destdir', '')
prefix = ARGUMENTS.get('prefix', '.')
libdir = ARGUMENTS.get('libdir', 'lib')
env_flags = ARGUMENTS.get('cxxflags', '')

flags = '-Wall -Wextra -Wconversion -ansi -pedantic ' + env_flags
if ARGUMENTS.get('enable-debug','0') == '1':
	flags += ' -g -ggdb'

dest = destdir + prefix
lib_path = dest + '/' + libdir
plugin_path = lib_path + '/sge'
bin_path = dest + '/bin'
media = '/share/games/sge'
media_path = dest + media
header_path = dest + '/include/sge'

core = Environment(LIBS = ['boost_filesystem', 'boost_signals', 'boost_regex', 'X11', 'dl'], CCFLAGS = flags, CPPDEFINES = {'PLUGIN_PATH':"\\\"" + prefix + '/' + libdir + '/sge' + "\\\"", 'MEDIA_PATH':"\\\"" + prefix + media + "\\\""})
libcore = core.SharedLibrary('sgecore', [glob('src/src/*.cpp'),
                                         glob('src/detail/src/*.cpp'),
                                         glob('src/renderer/src/*.cpp'),
                                         glob('src/sprite/src/*.cpp'),
                                         glob('src/texture/src/*.cpp'),
                                         glob('src/input/src/*.cpp'),
                                         glob('src/image/src/*.cpp'),
#                                         glob('src/console/src/*.cpp')
                                        ])

gui = Environment(LIBPATH = ['.'], LIBS = ['boost_filesystem', 'boost_signals', 'sgecore'], CCFLAGS = flags)
libgui = gui.SharedLibrary('sgegui', [glob('src/gui/src/*.cpp')])

ogl = Environment(LIBS = ['GL', 'X11', 'GLEW', 'Xxf86vm'], CCFLAGS = flags)
libogl = ogl.SharedLibrary('sgeogl', [glob('src/plugins/ogl/src/*.cpp')])

devil = Environment(LIBS = ['IL', 'ILU'], CCFLAGS = flags)
libdevil = devil.SharedLibrary('sgedevil', [glob('src/plugins/devil/src/*.cpp')])

freetype = Environment(LIBS = ['freetype'], CCFLAGS = flags)
freetype.Append(CCFLAGS = ' -I/usr/include/freetype2')
libfreetype = freetype.SharedLibrary('sgefreetype', [glob('src/plugins/freetype/src/*.cpp')])

xinput = Environment(LIBS = ['X11', 'Xxf86dga'], CCFLAGS = flags)
if ARGUMENTS.get('enable-dga','0') == '1':
	xinput.Append(CPPDEFINES = {'USE_DGA': 1 })
libxinput = xinput.SharedLibrary('sgexinput', [glob('src/plugins/xinput/src/*.cpp')])

wave = Environment(CCFLAGS = flags)
libwave = wave.SharedLibrary('sgewave', [glob('src/plugins/wave/src/*.cpp')])

vorbis = Environment(LIBS = ['vorbisfile'], CCFLAGS = flags)
vorbis.ParseConfig('pkg-config --libs vorbis')
libvorbis = vorbis.SharedLibrary('sgevorbis', [glob('src/plugins/vorbis/src/*.cpp')])

openal = Environment(LIBS = ['openal', 'alut'], CCFLAGS = flags)
libopenal = openal.SharedLibrary('sgeopenal', [glob('src/plugins/openal_player/src/*.cpp')])

#d3d = Environment(CPPPATH = ['/usr/include/wine/windows'], CCFLAGS = env_flags)
#libd3d = d3d.SharedLibrary('sged3d', [glob('src/plugins/d3d/src/*.cpp')])

#dinput = Environment(CPPPATH = ['/usr/include/wine/windows'], CCFLAGS = env_flags)
#libdinput = dinput.SharedLibrary('sgedinput', [glob('src/plugins/dinput/src/*.cpp')])

test = Environment(LIBPATH = ['.'], LIBS = ['sgecore','sgegui'], CCFLAGS = flags)
testapp = test.Program('sgetest', ['test/test.cpp'])

installer = Environment()
installer.Alias(target = "install", source = [core.Install(lib_path,libcore),
                                              gui.Install(lib_path,libgui),
                                              ogl.Install(plugin_path,libogl),
                                              devil.Install(plugin_path,libdevil),
                                              freetype.Install(plugin_path,libfreetype),
                                              xinput.Install(plugin_path,libxinput),
                                              wave.Install(plugin_path,libwave),
                                              vorbis.Install(plugin_path,libvorbis),
                                              openal.Install(plugin_path,libopenal),
                                           #  d3d.Install(plugin_path,libd3d),
                                              test.Install(bin_path,testapp),
                                              installer.Install(header_path,[glob('src/*.hpp')]),
                                              installer.Install(header_path + '/detail',[glob('src/detail/*.hpp')]),
                                              installer.Install(header_path + '/audio',[glob('src/audio/*.hpp')]),
                                              installer.Install(header_path + '/audio/audio_player',[glob('src/audio/audio_player/*.hpp')]),
                                              installer.Install(header_path + '/audio/audio_loader',[glob('src/audio/audio_loader/*.hpp')]),
                                              installer.Install(header_path + '/font',[glob('src/font/*.hpp')]),
                                              installer.Install(header_path + '/gui',[glob('src/gui/*.hpp')]),
                                              installer.Install(header_path + '/image',[glob('src/image/*.hpp')]),
                                              installer.Install(header_path + '/input',[glob('src/input/*.hpp')]),
                                              installer.Install(header_path + '/math',[glob('src/math/*.hpp')]),
                                              installer.Install(header_path + '/renderer',[glob('src/renderer/*.hpp')]),
                                              installer.Install(header_path + '/sprite',[glob('src/sprite/*.hpp')]),
                                              installer.Install(header_path + '/texture',[glob('src/texture/*.hpp')]),
                                              installer.Install(media_path, [glob('media/*')]),
                                              installer.Install(media_path + '/mainskin',[glob('media/mainskin/*')]),
                                              installer.Install(media_path + '/fonts',[glob('media/fonts/*')])
                                              ])
