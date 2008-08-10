/** 
\mainpage Welcome to sge
\section sec1 Using sge
In this small tutorial we'll first write a program which displays an image
on the screen. We'll then modify this program to move the image on the
screen using the arrow keys on your keyboard or the mouse.

\section sec2 Initializing sge subsystems
We want to draw an image on the screen, so we need at least two things: An
<em>image loader</em> and a <em>renderer</em>. We also need to initialize the
sge "core". 

Normally, you would have to get a renderer and an image loader plugin, load
them and create the according renderers and image loaders from those plugins,
but there's a shortcut which we'll take here since it's probably your first
glance at sge. 

To initialize sge we create a sge::systems object, which will handle the dirty
details of initialization for us. That's a one liner

\code
sge::systems sys;
\endcode

You have to include <sge/systems.hpp> for that. Now we can start initializing, first the core and the image loader:

\code
sys.init<sge::init::core>();
sys.init<sge::init::image_loader>();
\endcode



\section FAQ
<ul>
<li><b>Why the name "sge"?</b>

The name stems from Freundlich's (the original author's) intention to
program an engine for a "space game" of some sort. Long namespaces are,
However, tideous to write, so it came down to "sge".
<li><b>Why a new engine in C++, there are numerous others like irrlicht or ogre?</b>

TODO: Freundlich, write some rant about the horrible C++ those engines use
</ul>
*/

/*
 * Suggestion for longer initialization code
 *
 sge supports multiple renderers
(DirectX and OpenGL) and image loaders, so those systems aren't "hard coded"
into the engine, but they are <em>plugins</em>. So the first thing we create is
a <em>plugin manager</em>. That's a one liner: 
\code 
sge::plugin::manager pm;
\endcode
You need to include <sge/plugin/manager.hpp> for that.

Next, we need to get a <em>renderer plugin</em>. sge::plugin::manager has the
function \link sge::plugin::manager::get_plugin get_plugin \endlink to do just
that. This function is a template and it's template type determines which
plugin you want to load. This is the code to get a renderer plugin (or renderer
<em>system</em>):

\code
sge::plugin::plugin<sge::renderer::system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer::system>().load();
\endcode

Whew, it's a one-liner but not a very good one! If you don't want to know
what's going on, skip to the next paragraph, it's not very important for your
future sge skills, anyway. For all the others, let's dissect this line one by
one. You can see we're calling the mentioned \link
sge::plugin::manager::get_plugin get_plugin \endlink function, giving it
sge::renderer::system as template parameter. This system, however, isn't
<em>loaded</em> yet, so we call the suggestively named function \link
sge::plugin::context::load load \endlink. What we get back is a (smart) pointer
to a sge::plugin::plugin<sge::renderer::system>, which we have to keep
somewhere so the plugin isn't unloaded.

So we've got a renderer plugin, but a plugin isn't really a renderer. So there's just one more step ahead.
*/
