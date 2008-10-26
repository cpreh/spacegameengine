/**
\page tut_vertexformat Vertex Format
\section abstract Abstract
Every 3D application needs some sort of geometry. In most cases this geometry
is represented by triangles which in turn consist of three edges.
The data associated with those edges is called a vertex (like position,
normals, and so forth).

\section vertex_elements Vertex Elements
Because there is a huge number of possibilities for a vertex to look like
sge implements a vertex composition method, that is completly compile time
safe. First there are some classes that specify the role of a vertex's
subelement and what the element looks like.
Consider we are satisfied with vertices that only consist of positions
at the moment. We could write something like this:

\code
typedef sge::renderer::vf::pos<
	double,
	3
> pos_type;
\endcode

<em> pos_type </em> is not useful on its own, but it tells what this
vertex element should look like: It consists of 3 doubles and has the
role <em> pos </em> associated with it. Of course you could use 4 elements,
use float as coordinate type and so forth.

Next we want our vertex format to have a color, too.

\code
typedef sge::renderer::vf::color<
	sge::renderer::rgba8_color
> color_type;
\endcode

sge knows some color layouts like rgba8, argb8 and rgbaf32. Here we tell
that the vertex format's color should be in rgba and every color channel
should be 8 bits wide.


\subsection assemble_vertex_format Assembling the vertex format

Now that our elements are specified we can define our vertex format:

\code
typedef sge::renderer::vf::format<
	boost::mpl::vector<
		pos_type,
		color_type
	>
> format;

\endcode

That's it! We now have our vertex format.
But a vertex format on its own isn't very interesting.
We want a vertex buffer to fill some vertices in, so
let's create one.

\subsection create_vertex_buffer Creating the vertex buffer

\code

sge::renderer::vertex_buffer_ptr const vb(
	rend->create_vertex_buffer(
		sge::renderer::vf::make_dynamic_format<format>(),
		3,
		sge::renderer::resource_flags::none));

\endcode

For a renderer <em> rend </em> this creates a vertex buffer for us
with space for three vertices.
<em> sge::renderer::resource_flags::none </em> tells the renderer
that we are not interested in reading this vertex buffer's data back.
The strange <em> sge::renderer::vf::make_dynamic_format </em> is
needed to create a dynamic vertex format structure out of our
compile time safe format. The reason behind this is that plugins
can't involve templates for arbitrary types in their interfaces.
So for example opengl will use the dynamic format structure to
determine how to setup our vertex buffer.
The reason why the compile time safe format doesn't implicitly convert
into a dynamic format is solely to reduce dependency bloat.
If this was the case every header where you define your vertex format
would pull in the whole dynamic format's definitions.

\subsection fill_vertices Filling the vertices

Now to the interesting part: We want to fill our vertex buffer with data.
To do this we have to lock the buffer first.
sge's design of renderer resources always involves a lock to read or
write the data. This has several advantages such as that the data to read from
or to write to is mapped in memory. This offers the possibility for dma
transfers. Second, everything about a renderer resource is immutable
except its content. So resource allocation is not mixed with filling the data.

\code

sge;:renderer::scoped_vertex_lock const vblock(
	sge::renderer::make_scoped_lock(
		vb,
		sge::renderer::lock_flags::writeonly));

\endcode

scoped_lock is an RAII class that frees the lock in its destructor.
<em> sge::renderer::lock_flags::writeonly </em> tells the renderer
that we are only interested in writing to that buffer.
We could have specified <em> sge::renderer::lock_flags::readwrite </em>
instead but this would have failed at runtime because we didn't create
a readable buffer.
There is also another overload of make_scoped_lock so that you can
get a <em> const_scoped_vertex_lock </em> which is for reading only.

We can't use the lock directly to write our vertices, instead we have to
create a <em> sge::renderer::vf::view </em> from it.

\code
typedef sge::renderer::vf::view<
	format
> vertex_view;

vertex_view const view(
	vblock.value());
\encode

<em> sge::renderer::scoped_vertex_lock::value </em> returns a 
dynamic vertex view which can be converted into our compile time safe 
vertex view. There is also a check involved to see if they are compatible.
The easiest way to fill in our data is to use an iterator.
Here is how:

\code
typedef vertex_view::iterator iterator;
iterator it = view.begin();
\endcode

The iterator's reference type is a vertex. This structure finally lets you
fill in the vertex data.

\code
typedef iterator::reference vertex_ref;

vertex_ref r(*it);
\encode

Getting a reference to a vertex is just for exposition. Now we will see
how to set a vertex with this.

\code
typedef pos_type::packed_type vec3;

r.set<pos_type>(
	vec3(
		-1.,
		1.,
		0.));
\endcode

This sets the first vertex's position of our vertex buffer to (-1, 1, 0).
Note the dots behind the numbers: They turn our numbers into double literals.
Next we set the color, too.

\code
typedef color_type::packet_type col4;

r.set<color_type>(
	col4(
		255,
		255,
		0,
		255));
\encode

This sets the color to yellow with 100% opacity.
We could have also used sge's color constant to do that.

\code
r.set<color_type>(
	sge::renderer::color_convert<col4>(
		sge::renderer::colors::yellow));
\encode

The iterator can, of course, be incremented to reach the other two
vertices in the buffer. A vertex iterator is a <em> random access iterator
</em>.
*/
