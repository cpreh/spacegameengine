/** 
\page tut_begin sge tutorial
\section abstract Abstract
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

You have to include <sge/systems.hpp> for that. Now we can start initializing,
first the core and the image loader:

\code
sys.init<sge::init::core>();
sys.init<sge::init::image_loader>();
\endcode

The header belonging to \link sge::init init \endlink is <sge/init.hpp>.

Then, for the renderer, we need to choose a window resolution and pass it to
\link sge::systems::init init \endlink:

\code
sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));
\endcode

And that's it. If you start the program now you probably see a 640x480 window
popping up for a split second. Our first sge program! Just for convenience,
here's the whole program:

\code
#include <sge/systems.hpp>
#include <sge/init.hpp>

int main()
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::image_loader>();
	sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));
}
\endcode

Now that we've initialized the subsystems, we can access them via
<tt>sys.renderer</tt> and <tt>sys.image_loader</tt>.

\section sec3 Drawing an image

The next goal is to draw an image on our newly created window which we can move
around later on. In computer graphics, a two dimensional "object" is called a
<em>sprite</em>. To draw one or more sprites in sge you have to create a
sge::sprite::system, which gets the renderer in its constructor.

\code
sge::sprite::system ss(sys.renderer);
\endcode

To declare a variable of type sge::sprite::system somewhere, you need to include
<sge/sprite/system.hpp>. To \em use it, however, another header,
<sge/sprite/system_impl.hpp>, is needed. This is because the system's \link
sge::sprite::system::render render \endlink function is a template and by not
including it by default, compile time is saved. You'll see this often in sge
headers, so if you wonder why you get <em>undefined references</em> when
compiling your code, look for missing <em>_impl</em> headers.

Now for the tricky part, loading the image and attaching it to a sge::sprite.
First, we use the image loader to load the image:

\code
sge::image::object_ptr image = sys.image_loader->load_image(SGE_TEXT("testimage.png"));
\endcode

There are a few new things here, first of all <tt>sys.image_loader</tt> is a
smart pointer, so we cannot use the . (dot) operator to access the \link
sge::image::loader::load_image load_image \endlink function. The same applies
to renderer and any other subsystem class.

And what about this strange SGE_TEXT thingy around the string? Well, if you want
to use character literals in sge, they have to be <em>narrow</em> literals and
you have to embrace them with SGE_TEXT; all this macro does is convert the literal to
sge::string's internal format (which is wide or narrow, depending on the FOOBAR
macro which you can specify when you compile sge).

The rest of the code should be pretty clear, the load_image function returns an
sge::image::object_ptr (again a smart pointer) which we assign to the variable
<em>image</em>.

Okay, now we've got an image, but a sprite needs a <em>texture</em> which is
stored in the fast VRAM of your graphics card instead of the system RAM.
Creating textures is the renderer's job:

\code
sge::renderer::texture_ptr image_texture = sys.renderer->create_texture(image->view(),sge::renderer::linear_filter);
\endcode

Files to include: <sge/renderer/texture_filter.hpp>

This version of \link sge::renderer::device::create_texture create_texture
\endlink takes a <em>renderer::const_image_view</em>. Luckily, our image object
has a \link sge::image::object::view view \endlink function which returns just
this. The second argument is the filter which is applied to the texture when
it's rendered. Linear filter actually blurs the texture a bit, but it's the
filter you'll most often want to use for sprites. An alternative would be
sge::renderer::point_filter, which does no filtering at all, so with enlarged
low resolution images, pixels can be seen.

Anyway, in theory, we would now be able to use the texture to paste it onto a
sprite. If you look at the constructor of sge::sprite::object you'll see that it
doesn't take a <em>texture_ptr</em>, but a <em>part_ptr</em>. That's because you
don't have to create a separate texture for each sprite, but you can also create
a big texture containing smaller sub textures and assign those sub textures to
the sprites. This is called "atlasing" and can really boost performance since
changing the current texture on the videocard is considered expensive.

Since we're not going to use atlasing in the tutorial, we create a part which is
just a wrapper for a single texture. Watch!

\code
sge::sprite::object my_object(
	sge::sprite::point(0,0),
	sge::texture::part_ptr(new sge::texture::part_raw(image_texture)));
\endcode

Files to include: <sge/texture/part_raw.hpp>, <sge/sprite/object.hpp>

This piece of code should be pretty self explanatory now. Note that
<tt>my_object</tt> is not a smart pointer but a "real" object. We put the sprite
on the top left corner of the screen and give it our test texture. If no size is
specified, the default behaviour for a sprite is to be as large as its texture.

\subsection The main loop

Having created all the stuff we need, the program still closes immediately after
starting it. So let's add a main loop which keeps it going!

\code
std::vector<sge::sprite::object> sprites;
sprites.push_back(my_object);

while (true)
{
	sge::window::dispatch();
	sge::renderer::scoped_block block_(sys.renderer);
	ss.render(sprites.begin(),sprites.end());
}
\endcode

Files to include: <vector>, <sge/renderer/scoped_block.hpp>.

Being a <em>system</em> after all, sge::sprite::system can manage more than one
sprite. So we create a container (a std::vector) and put all the sprites we
want to draw into it - which is, of course, just one right now. Don't worry,
sprites are very lightweight, copying isn't an expensive operation.

Inside the endless loop (we'll fix that when we introduce the <em>input
system</em>), sge::window::dispatch is called. This is just a maintenance
function so the window properties are updated. You can try removing this line
and see what happens if you like.

If you want to render something on the screen, you have to call
renderer::begin_rendering and renderer::end_rendering. Yet, since we write our code
exception safe (!), we use the renderer::scoped_block class which calls these
functions in its constructor and destructor.

Finally, we tell the sprite system to render our sprite.

Here's the complete program:

\code
#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/system_impl.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/texture/part_raw.hpp>
#include <vector>

int main()
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::image_loader>();
	sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));

	sge::sprite::system ss(sys.renderer);
	sge::image::object_ptr image = sys.image_loader->load_image(SGE_TEXT("testimage.png"));
	sge::renderer::texture_ptr image_texture = sys.renderer->create_texture(image->view(),sge::renderer::linear_filter);
	sge::sprite::object my_object(
			sge::texture::part_ptr(new sge::texture::part_raw(image_texture)));
			image_texture);

	std::vector<sge::sprite::object> sprites;
	sprites.push_back(my_object);

	while (true)
	{
			sge::window::dispatch();
			sge::renderer::scoped_block block_(sys.renderer);
			ss.render(sprites.begin(),sprites.end());
	}
}
\endcode

Now we can move on to \ref tutorial_2 "part 2" of the tutorial, where we add input support.
*/
