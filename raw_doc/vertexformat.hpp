/**
\page tut_vertexformat Vertex Format
\section abstract Abstract
Every 3D application needs some sort of geometry. In most cases this geometry
is represented by triangles which in turn consist of three points.
The data associated with those points is called a vertex (like position,
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

Files to include: <sge/renderer/vf/pos.hpp>

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

Files to include: <sge/renderer/vf/color.hpp>, <sge/renderer/color.hpp>

sge knows some color layouts like rgba8, argb8 and rgbaf32. Here we tell
that the vertex format's color should be in rgba and every color channel
should be 8 bits wide.


\section assemble_vertex_format Assembling the vertex format

Now that our elements are specified we can define our vertex format:

\code
typedef sge::renderer::vf::format<
	boost::mpl::vector<
		pos_type,
		color_type
	>
> format;

\endcode

Files to include: <sge/renderer/vf/format.hpp>, <boost/mpl/vector.hpp>

That's it! We now have our vertex format.
But a vertex format on its own isn't very interesting.
We want a vertex buffer to fill some vertices in, so
let's create one.

\section create_vertex_buffer Creating the vertex buffer

\code

sge::renderer::vertex_buffer_ptr const vb(
	rend->create_vertex_buffer(
		sge::renderer::vf::make_dynamic_format<format>(),
		3,
		sge::renderer::resource_flags::none));

\endcode

Files to include: <sge/renderer/device.hpp>, <sge/renderer/vertex_buffer.hpp>,
<sge/renderer/vf/make_dynamic_format.hpp>

For a renderer <em> rend </em> this creates a vertex buffer for us
with space for three vertices.
sge::renderer::resource_flags::none tells the renderer
that we are not interested in reading this vertex buffer's data back.
The strange  sge::renderer::vf::make_dynamic_format is
needed to create a dynamic vertex format structure out of our
compile time safe format. The reason behind this is that plugins
can't involve templates for arbitrary types in their interfaces.
So for example opengl will use the dynamic format structure to
determine how to setup our vertex buffer.
The reason why the compile time safe format doesn't implicitly convert
into a dynamic format is solely to reduce dependency bloat.
If this was the case every header where you define your vertex format
would pull in the whole dynamic format's definitions.

\section fill_vertices Filling the vertices

Now to the interesting part: We want to fill our vertex buffer with data.
To do this we have to lock the buffer first.
sge's design of renderer resources always involves a lock to read or
write the data. This has several advantages such as that the data to read from
or to write to is mapped in memory. This offers the possibility for dma
transfers. Second, everything about a renderer resource is immutable
except its content. So resource allocation is not mixed with filling the data.

\code

sge::renderer::scoped_vertex_lock const vblock(
	sge::renderer::make_scoped_lock(
		vb,
		sge::renderer::lock_flags::writeonly));

\endcode

Files to include: <sge/renderer/scoped_vertex_lock.hpp>

scoped_lock is an RAII class that frees the lock in its destructor.
sge::renderer::lock_flags::writeonly tells the renderer
that we are only interested in writing to that buffer.
We could have specified sge::renderer::lock_flags::readwrite
instead but this would have failed at runtime because we didn't create
a readable buffer.
There is also another overload of make_scoped_lock so that you can
get a <em> const_scoped_vertex_lock </em> which is for reading only.

We can't use the lock directly to write our vertices, instead we have to
create a sge::renderer::vf::view from it.

\code
typedef sge::renderer::vf::view<
	format
> vertex_view;

vertex_view const view(
	vblock.value());
\endcode

Files to include: <sge/renderer/vf/view.hpp>

sge::renderer::scoped_vertex_lock::value returns a 
dynamic vertex view which can be converted into our compile time safe 
vertex view. There is also a check involved to see if they are compatible.
The easiest way to fill in our data is to use an iterator.
Here is how:

\code
typedef vertex_view::iterator iterator;
iterator it = view.begin();
\endcode

Files to include: <sge/renderer/vf/iterator.hpp>

The iterator's reference type is a vertex. This structure finally lets you
fill in the vertex data.

\code
typedef iterator::reference vertex_ref;

vertex_ref r(*it);
\endcode

Files to include: <sge/renderer/vf/vertex.hpp>

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
The packed_type of a vertex element's role is the associated compound type
for this element. In this case this will be an
sge::math::vector::static_<double, 3>::type.
Next we set the color, too.

\code
typedef color_type::packed_type col4;

r.set<color_type>(
	col4(
		255,
		255,
		0,
		255));
\endcode

This sets the color to yellow with 100% opacity.
Remember that we used sge::renderer::rgba8_color for our color channel.
The constructor's argument order is determined by the order of the format
itself.
sge offers a lot of predefined colors.
We could have also used the yellow constant to set the color.

\code
r.set<color_type>(
	sge::renderer::color_convert<col4>(
		sge::renderer::colors::yellow()));
\endcode

Files to include: <sge/renderer/colors.hpp>, <sge/renderer/color_convert.hpp>

The iterator can, of course, be incremented to reach the other two
vertices in the buffer. A vertex iterator is a <em> random access iterator
</em>.

\section vertex_roles Vertex roles

So far we have seen how to create a vertex format for a position and a color.
There are, however, more possible roles and some even can be used more than
once.

The next code snippet shows how to declare a <em> normal role </em>.

\code
typedef sge::renderer::vf::normal<
	float
> normal_type;
\endcode

Files to include: <sge/renderer/vf/normal.hpp>

Notice the absence of the element count type.
Normals always have to consist of three subelements, namely x, y and z.

We can also declare a <em>texture coordinate role</em>.

\code
typedef sge::renderer::vf::texpos<
	float,
	2
> texpos_type;
\endcode

Files to include: <sge/renderer/vf/texpos.hpp>

This role should be used with 2-dimensional textures only.

Lastly, the vertex format also supports an <em>unspecific role</em>.
This role can be used with any data and is meant as additional input to
a shader.
The syntax is similar to the other vertex element roles you have just seen.
Which kind of data an <em>unspecific role</em> holds is determined by
two template parameters: First the element type and second the element count.

\code
typedef sge::renderer::vf::unspecified<
	float,
	3
> unspec_vec3; // vector of three floats

typedef sge::renderer::vf::unspecified<
	double,
	1
> unspec_d1; // single value of double

typedef sge::renderer::vf::unspecified<
	sge::renderer::bgra8_color
> unspec_bgra8; // bgra8 color
\endcode

Files to include: <sge/renderer/vf/unspecified.hpp>

The magic the <em>unspecified</em> template does here is just for
convenience. You could have used the base types of the vertex roles as well,
as you can with the other vertex roles.

\section multiple_roles Multiple roles of the same type

There is multi texturing in 3D applications so we might want
to specify more than one texture coordinate.
Here is how we do that:

\code
typedef sge::renderer::vf::format<
	boost::mpl::vector<
		texpos_type,
		texpos_type
	>
> format;
\endcode

Simply repeat the role's type in the mpl::vector to get the role twice!
The next thing is: How do we access multiple elements of the same
role type through a vertex?
Here is how:

\code
vertex &r(*it); // suppose we already have the other stuff in place

typedef texpos_type::packed_type texp;

r.set<texpos, 0>(
	texp(
		0.f
		1.f));

r.set<texpos, 1>(
	texp(
		0.f,
		1.f));
\endcode

<em> set </em> is a template function whose second argument defaults to 0.
So set<type> is equivalent to set<type, 0>. If you choose a different index
than 0, you can set the other vertex elements besides the first.
The example above would set both texture coordinates of the vertex to the
same value.

\section limitations_multiple_roles Limitations of multiple roles

More than one <em>pos role</em> is meaningless. It is therefore not allowed.
The same goes for more than one <em>normal role</em>.
At the moment only one <em>color role</em> is supported.
There can be up to an implementation defined number of <em>texture pos roles</em>
and <em>unspecified roles</em> in the vertex format.

\section limitations_element_types Limitations of the element types

For a <em> pos role </em> only 2, 3 or 4 subelement types are accepted.
Their types must be either float or double.

A <em> normal role's </em> type must be either float or double.

For the <em> color roles </em> only the predefined colors in
<sge/renderer/color.hpp> are accepted.

The <em> texture roles </em> must have 2 or 3 subelements.
Their types must be either float or double.

\section reading_vertices Reading vertices

Our code earlier disabled the reading of vertices.
For most parts there is a good reason to: Reading back vertex data is slow.
If you choose not to read the data back like we did, their contents will be
initially undefined (this is even true if you choose to read them back but the
vertices have not been initialized yet).
However, you can read the vertex data out that you
have just written before unlocking the buffer (which means that our
scoped lock goes out of scope).
We take the code for writing a vertex's position and read it right back.

\code

typedef pos_type::packed_type vec3;

r.set<pos_type>(
	vec3(
		-1.,
		1.,
		0.));

vec3 const v(
	r.get<pos_type>());

\endcode

<em> get </em> of course also takes an index which defaults to zero.

\code
vertex &r(*it);

typedef texpos_type::packed_type texp;

r.set<texpos, 0>(
	texp(
		0.f
		1.f));

r.set<texpos, 1>(
	texp(
		0.f,
		1.f));

texp const tex1(
	r.get<texpos, 1>);

\endcode

\section vertex_design Design reasons

The vertex format is designed so that it is compile time safe.
This means that if you accidently try to access a vertex element whose role
has not been specified you will get a compile time error.
Exposing more type information to the compiler can also have positive impact
on performance.

<em> set </em> and <em> get </em> take and return the elements by value.
This means you can't get a reference to your vertices or vertex elements.
The reason behind this is the same why we need a dynamic format in the first
place. A vertex buffer interface can't return arbitrary types so we have to
stick to the only method of passing binary data: Use a raw array of
<em> unsigned char </em>. Because C++'s aliasing rules are very strict,
we are allowed to copy any data in such an array or copy any data out but
building a pointer of a different type to an array of <em> unsigned char </em>
and dereferencing it is undefined behaviour (this is, of course not true if
the static type of the raw array is in fact the type we casted back to, but
this is obviously not possible here).

*/
