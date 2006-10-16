from glob import glob

workdir = ARGUMENTS.get('workdir', '')
prefix = ARGUMENTS.get('prefix', '.')
libdir = ARGUMENTS.get('libdir', 'lib')
argflags = ARGUMENTS.get('flags', '')

flags = '-Wall -ansi -pedantic -g' + argflags
lib_path = workdir + prefix + '/' + libdir
plugin_path = lib_path + '/sge'
bin_path = workdir + prefix + '/bin'
media_path = prefix + '/share/games/sge'
header_path = workdir + prefix + '/include/sge'

core = Environment(LIBS = ['boost_filesystem', 'boost_signals', 'X11', 'dl'], CCFLAGS = flags, CPPDEFINES = {'PLUGIN_PATH':"\\\"" + prefix + '/' + libdir + '/sge' + "\\\"", 'MEDIA_PATH':"\\\"" + media_path + "\\\""})
libcore = core.SharedLibrary('sgecore', [glob('./src/src/*.cpp'),
                                         glob('./src/renderer/src/*.cpp'),
                                         glob('./src/sprite/src/*.cpp')])

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
libxinput = xinput.SharedLibrary('sgexinput', [glob('./src/plugins/xinput/src/*.cpp')])

#d3d = Environment(LIBS = ['winelib'], CCFLAGS = flags)
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
                                              test.Install(bin_path,testapp),
                                              installer.Install(header_path,[glob('./src/*.hpp')]),
                                              installer.Install(header_path + '/audio',[glob('./src/audio/*.hpp')]),
                                              installer.Install(header_path + '/font',[glob('./src/font/*.hpp')]),
                                              installer.Install(header_path + '/gui',[glob('./src/gui/*.hpp')]),
                                              installer.Install(header_path + '/image',[glob('./src/image/*.hpp')]),
                                              installer.Install(header_path + '/input',[glob('./src/input/*.hpp')]),
                                              installer.Install(header_path + '/math',[glob('./src/math/*.hpp')]),
                                              installer.Install(header_path + '/renderer',[glob('./src/renderer/*.hpp')]),
                                              installer.Install(header_path + '/sprite',[glob('./src/sprite/*.hpp')])#,
#					      installer.Install(media_path,[glob('./media/*')])
					      ])
