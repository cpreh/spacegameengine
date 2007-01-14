from glob import glob

destdir = ARGUMENTS.get('destdir', '')
prefix = ARGUMENTS.get('prefix', '.')
libdir = ARGUMENTS.get('libdir', 'lib')
env_flags = ARGUMENTS.get('cxxflags', '')

flags = '-Wall -Wextra -ansi -pedantic ' + env_flags
if ARGUMENTS.get('enable-debug','0') == '1':
	flags += ' -g -ggdb'

dest = destdir + prefix
lib_path = dest + '/' + libdir
plugin_path = lib_path + '/sge'
bin_path = dest + '/bin'
media = '/share/games/sge'
media_path = dest + media
header_path = dest + '/include/sge'

core = Environment(LIBS = ['boost_filesystem', 'boost_signals', 'X11', 'dl'], CCFLAGS = flags, CPPDEFINES = {'PLUGIN_PATH':"\\\"" + prefix + '/' + libdir + '/sge' + "\\\"", 'MEDIA_PATH':"\\\"" + prefix + media + "\\\""})
libcore = core.SharedLibrary('sgecore', [glob('./src/src/*.cpp'),
                                         glob('./src/renderer/src/*.cpp'),
                                         glob('./src/sprite/src/*.cpp'),
                                         glob('./src/texture/src/*.cpp'),
                                         glob('./src/input/src/*.cpp')])

gui = Environment(LIBPATH = ['.'], LIBS = ['boost_filesystem', 'boost_signals', 'sgecore'], CCFLAGS = flags)
libgui = gui.SharedLibrary('sgegui', [glob('./src/gui/src/*.cpp')])

ogl = Environment(LIBS = ['GL', 'X11', 'GLEW', 'Xxf86vm'], CCFLAGS = flags)
libogl = ogl.SharedLibrary('sgeogl', [glob('./src/plugins/ogl/src/*.cpp')])

devil = Environment(LIBS = ['IL', 'ILU'], CCFLAGS = flags)
libdevil = devil.SharedLibrary('sgedevil', [glob('./src/plugins/devil/src/*.cpp')])

freetype = Environment(LIBS = ['freetype'], CCFLAGS = flags)
freetype.Append(CCFLAGS = ' -I/usr/include/freetype2')
libfreetype = freetype.SharedLibrary('sgefreetype', [glob('./src/plugins/freetype/src/*.cpp')])

xinput = Environment(LIBS = ['X11', 'Xxf86dga'], CCFLAGS = flags)
#if(ARGUMENTS.find('--enable-dga'))
#	xinput.Append(CPPDEFINES = {'USE_DGA', 1})
libxinput = xinput.SharedLibrary('sgexinput', [glob('./src/plugins/xinput/src/*.cpp')])

#d3d = Environment(CPPPATH = ['/usr/include/wine/windows'], CCFLAGS = argflags + ' /usr/lib/wine/d3d9.dll.so')
#libd3d = d3d.SharedLibrary('sged3d', [glob('./src/plugins/d3d/src/*.cpp')])

test = Environment(LIBPATH = ['.'], LIBS = ['sgecore','sgegui'], CCFLAGS = flags)
testapp = test.Program('sgetest', ['./test/test.cpp'])

installer = Environment()
installer.Alias(target = "install", source = [core.Install(lib_path,libcore),
                                              gui.Install(lib_path,libgui),
                                              ogl.Install(plugin_path,libogl),
                                              devil.Install(plugin_path,libdevil),
                                              freetype.Install(plugin_path,libfreetype),
                                              xinput.Install(plugin_path,libxinput),
                                           #  d3d.Install(plugin_path,libd3d),
                                              test.Install(bin_path,testapp),
                                              installer.Install(header_path,[glob('./src/*.hpp')]),
                                              installer.Install(header_path + '/audio',[glob('./src/audio/*.hpp')]),
                                              installer.Install(header_path + '/font',[glob('./src/font/*.hpp')]),
                                              installer.Install(header_path + '/gui',[glob('./src/gui/*.hpp')]),
                                              installer.Install(header_path + '/image',[glob('./src/image/*.hpp')]),
                                              installer.Install(header_path + '/input',[glob('./src/input/*.hpp')]),
                                              installer.Install(header_path + '/math',[glob('./src/math/*.hpp')]),
                                              installer.Install(header_path + '/renderer',[glob('./src/renderer/*.hpp')]),
                                              installer.Install(header_path + '/sprite',[glob('./src/sprite/*.hpp')]),
                                              installer.Install(header_path + '/texture',[glob('./src/texture/*.hpp')]),
                                              installer.Install(media_path + '/mainskin',[glob('./media/mainskin/*')])
                                              ])
