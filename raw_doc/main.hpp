/**
\mainpage sge project site

\section tm The manual
- Tutorials:
	-# \subpage tut_begin
	-# \subpage tutorial_2
	-# \subpage textures
	-# \subpage tut_fonts
	-# \subpage console
- \subpage faq

\section hap History and purpose
I started this engine a few years ago. My primary aim at that time was to learn
and practice good C++. Today I would like to share my programming work and to
bring new developers and users to it. 

\section a Architecture
The engine is written in clean C++ and makes heavy use of RAII and the library
'boost'.

The whole user interface is standard C++ only and doesn't require the user to
include any non standard headers besides the engine's own headers nor to use
any platform or library dependant functions or structures. The aforementioned
headers are not even included indirectly (except the boost headers).

Specific backends like opengl are plugins which can be loaded and unloaded at
runtime. For every plugin type there is an abstract core interface plus
additional interfaces that can be obtained from those. Here are the plugin
types supported by sge: 

- audio_loader (wave, vorbis)
- audio_player (openal)
- font (freetype)
- image (devil)
- input (X11, direct input)
- renderer (opengl, direct3d9)

\section cs Current status
The current codebase in git is considered to be in alpha state. 

\subsection tfw The following works:
- Most opengl functionality.
- Mouse and keyboard using the X input plugin or the direct input plugin.
- Playing sounds using the openal audio plugin.
- Loading wave and ogg vorbis files.
- Loading images using the devil image plugin.
- 'Making' fonts using the freetype font plugin.
- Rendering fonts using the engine's font architecture.
- A full automated and texture efficient sprite engine.
- A console.
- Basic md3 loading support.
- Basic GLSL support.
- A gui with buttons, text edits, a list with vertical scrollbar, a checkbox, static text, graphical buttons and frames. (a new gui is currently under development.)

\subsection whtbd What has to be done:
- Some parts of the math library should be replaced with something more appropriate.
- 3d rendering facilities such as model loaders, scene graphs and more.
- HLSL and mabye Cg support.
- Joystick support.
- Of course there is always more…

\section htdl How to get it
You just enter the following in a terminal:

<tt>git clone git://git.tuxfamily.org/gitroot/sge/spacegameengine.git</tt>

\section htc How to compile 
You can either use cmake (which is recommended) or the Code::Blocks project
files.

Building plugins or the test application(s) is optional.

To start the build run <tt>cmake .</tt> and pass the options to enable what you
need. The following options may be specified: 

- <tt>-DCMAKE_INSTALL_PREFIX=/where/to/install</tt> (important: This is your installation destination which is usually /usr)
- <tt>-D ENABLE_DEVIL:=1</tt> (build the devil plugin)
- <tt>-D ENABLE_DINPUT:=1</tt> (build the direct input plugin)
- <tt>-D ENABLE_DGA:=1</tt> (build dga support)
- <tt>-D ENABLE_FREETYPE:=1</tt> (build the freetype plugin)
- <tt>-D ENABLE_GUI:=1</tt> (build the gui)
- <tt>-D ENABLE_OPENAL:=1</tt> (build the openal plugin)
- <tt>-D ENABLE_OPENGL:=1</tt> (build the opengl plugin)
- <tt>-D ENABLE_TEST:=1</tt> (build the test application)
- <tt>-D ENABLE_VORBIS:=1</tt> (build the vorbis plugin)
- <tt>-D ENABLE_WAVE:=1</tt> (build the wave plugin)
- <tt>-D ENABLE_XINPUT:=1</tt> (build the xinput plugin)

For Gentoo users an ebuild is provided in the repository. 

\section d Dependencies
<b>Note that some of these libraries may in turn require additional libraries by themselves.</b>
\subsection bt Build time
- cmake
- pkgconfig

\subsection c Core
- boost (1.35 or later is required)
- X (Linux only)

\subsection p Plugins
- devil: devil
- direct input: DirectX SDK
- freetype: freetype
- openal: openal
- opengl: glew, xf86vidmode (for optional fullscreen mode, Linux only)
- vorbis: libvorbis
- xinput: xf86dga (for optional dga support, Linux only)

*/
