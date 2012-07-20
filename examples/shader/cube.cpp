/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


/**
	Example description:

	This example displays a diffuse shaded cube with an rgb texture
	whose surface normals are perturbed by a normal map.

	This example shows the usage of:

	- sge::shader::object in general
	- multitexturing with shader::object
	- uniform and constant variables with shader::object
	- adapting the camera to the current viewport
	- a vertex format and how to fill it (see fill_vb_with_cube) in general
	- unspecified and builtin attributes (pos, texcoord)
	- sge::camera
	- viewport::fill_on_resize
	- planar texture creation
	- image loading
	- timers
	- font::text::draw
 */

#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/matrix_conversion/world_projection.hpp>
#include <sge/camera/spherical/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/camera/spherical/action/wasd_mapping.hpp>
#include <sge/camera/spherical/coordinate_system/look_down_positive_z.hpp>
#include <sge/config/media_path.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/metrics_scoped_ptr.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_shared_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/shader/activate_everything.hpp>
#include <sge/shader/activation_method.hpp>
#include <sge/shader/matrix.hpp>
#include <sge/shader/matrix_flags.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/object_parameters.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/scoped.hpp>
#include <sge/shader/update_single_uniform.hpp>
#include <sge/shader/variable.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/shader/vf_to_string.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cmath>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{
// A few words here about vertex formats in general:
//
// What's this all about? Well, the ultimate goal is to copy vertices
// to the GPU. To do that, the graphics APIs give you access to the
// graphics card's memory and return it as, say, a void pointer. You
// have to do two things:
// 1) You have to fill this buffer with the vertices. Of course, a
//    vertex has an arbitrary amount of data attached to it:
//    position, normal, texture coordinate and so on.
// 2) You have to tell the graphics API how many vertices there are
//    and what attributes they consist of.
// Using template magic and modern C++, this task is made pretty
// simple in sge. There are two parts: The definition of the format
// and the buffer filling stuff. First up: The definition...
namespace vf
{
// vf::pos is a "builtin" vertex attribute. This means, for example,
// that you don't have to specify it in a glsl shader (it's always
// accessible via gl_Vertex). Those attributes are, however,
// deprecated in newer OpenGL and DirectX versions. unspecified is the
// successor (see below)
typedef
sge::renderer::vf::pos
<
	// type and dimension of the position attribute values from 1 to 4 are possible
	sge::renderer::scalar,
	3
>
position;

// Again, a builtin attribute. This time, for (2D) texture
// coordinates. 2 to 4 dimensions are possible.
typedef
sge::renderer::vf::texpos
<
	sge::renderer::scalar,
	2
>
texcoord;

// An unspecified attribute has to have a "tag" which is...
// a) ...bound to a name in the shader (you can access it via "vertex_normal")
// b) ...an identifier for the vertex::set method
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(vertex_normal);
}

typedef
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector
	<
		sge::renderer::scalar,
		3
	>,
	// This binds the tag to the attribute
	tags::vertex_normal
>
vertex_normal;

// Since we're doing a coordinate transformation in the shader, we
// need two vectors to define a 3D basis. So here's the surface
// tangent.
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(vertex_tangent);
}

typedef
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector
	<
		sge::renderer::scalar,
		3
	>,
	tags::vertex_tangent
>
vertex_tangent;

// A vertex format can consist of multiple parts. You could, for
// example, store the texture coordinates in a vertex buffer and the
// positions in another. In this setting, you could update the
// positions while keeping the texture coordinates the same - a
// performance improvement.
//
// In this example, we define only one part which contains all 4
// attributes.
typedef
sge::renderer::vf::part
<
	// Note that here, there's no distinction between unspecified and
	// builtin.
	boost::mpl::vector4
	<
		position,
		texcoord,
		vertex_normal,
		vertex_tangent
	>
>
format_part;

// The "sum of its parts". Here, we have only one part. You have to
// watch out later on. Sometimes you need the whole vertex format,
// sometimes only a part.
typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<format_part>
>
format;

// The graphics API gives us a raw buffer, but we want to write to it
// in a natural kind of way, so we take a "view" on this buffer. See
// fill_vb_with_cube.
typedef
sge::renderer::vf::view<format_part>
format_part_view;
}

void
fill_vb_with_cube(
	sge::renderer::vertex_buffer &vb)
{
	// Then we lock the vertex buffer for writing. When this lock is
	// released, the data is sent the GPU.
	sge::renderer::scoped_vertex_lock const vblock(
		vb,
		sge::renderer::lock_mode::writeonly);

	// Create a view on the data.
	vf::format_part_view const vertices(
		vblock.value());

	// We now basically have a vector<vertex>, though which we can
	// iterate and set values. And that's what we're gonna do
	vf::format_part_view::iterator vb_it(
		vertices.begin());

	// This "vertex" class has a "set" function which can set arbitrary
	// vertex attributes. Which attribute it sets is determined by a
	// template parameter. You can pass all of the attributes defined
	// above.
	// _But_ there's a distinction between the _attribute type_ and the
	// _value type_ of the attribute. The position attribute, for
	// example, has type "sge::renderer::vf::pos<...>" which could be
	// anything. It's certainly _not_ a vector3, though. That's what the
	// ::packed_type is for.
	typedef
	vf::position::packed_type
	position_vector;

	typedef
	vf::vertex_normal::packed_type
	vertex_normal_vector;

	typedef
	vf::vertex_tangent::packed_type
	vertex_tangent_vector;

	typedef
	vf::texcoord::packed_type
	texcoord_vector;

	// Now we fill the vertex buffer which is pretty boring and tedious.
	// bottom 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// bottom 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// top 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// top 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// left 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// left 2
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// right 1
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// right 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// front 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// front 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// back 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// back 1
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it).set<vf::vertex_tangent>(
		vertex_tangent_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
}

// Hours of scrolling later, this function is just a helper function
// setting one single attribute. Note that we have to activate the
// shader, else we get an exception.
void
toggle_bumpmapping(
	sge::shader::object &shader,
	bool &enabled)
{
	enabled = !enabled;
	sge::shader::update_single_uniform(
		shader,
		"enabled",
		enabled ? 1 : 0);
}
}


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	// Turn on debug logging, just in case. :)
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance const sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge test for sge::shader::object")),
					// The window's "size hint". The window that is created
					// might not be 1024x768. It's up to the window manager to
					// decide how big the window will be. On windows, the window
					// will probably be 1024x768, but on Linux you have tiling
					// window managers which override this dimension. That's why
					// below, we equip ourselves for a viewport window size and
					// viewport that might change.
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					// We want 32 bit depth (for no apparent reason, reall)
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32),
					// and we want to do depth buffering
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				// This instructs sge to set the _viewport size_ to whatever
				// the _window size_ will be. If you don't know what the
				// difference between the viewport and the window is, read up
				// on it! It's important.
				sge::viewport::fill_on_resize()))
			(sge::systems::font())
			(sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("png"))))))
			(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector)
					| sge::systems::input_helper::mouse_collector,
				// This is important for any application that needs relative mouse movement:
				// An exclusive cursor won't be shown, nor will it be able
				// to click into other windows, so you don't lose the focus.
				// Switching the focus with your window manager is still possible.
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive))));

	// Load two images and create two textures from them.
	sge::renderer::texture::planar_shared_ptr const
		normal_texture(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()/FCPPT_TEXT("images")/FCPPT_TEXT("normal_map.png"),
				sys.renderer(),
				sys.image_system(),
				sge::renderer::texture::mipmap::off(),
				// Here, you could specify "readable", for example
				sge::renderer::resource_flags_field::null())),
		color_texture(
			sge::renderer::texture::create_planar_from_path(
				sge::config::media_path()/FCPPT_TEXT("images")/FCPPT_TEXT("color_map.png"),
				sys.renderer(),
				sys.image_system(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null()));

	// When escape is pressed, the main loop should end
	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	// The camera is a good debugging tool. It gives easy access to the
	// mvp matrix every shader needs. You can move around with 'w', 'a',
	// 's' and 'd' and you can look around using the mouse.
	sge::camera::spherical::object camera(
		sge::camera::spherical::parameters(
			sys.keyboard_collector(),
			sge::camera::spherical::is_active(
				true),
			sge::camera::spherical::coordinate_system::look_down_positive_z(
				sge::camera::spherical::coordinate_system::radius(
					3.0f)),
			sge::camera::spherical::action::wasd_mapping()));

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.renderer(),
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);

	// To use a vertex format, we have to create a _declaration_ and
	// some _buffers_.
	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	// Ah, the shader object
	sge::shader::object shader(
		sge::shader::object_parameters(
			sys.renderer(),
			*vertex_declaration,
			// This turns the vertex format we defined above into a glsl
			// variable declaration which replaces the '$$$HEADER$$$' magic
			// string in the glsl files (not completely though, HEADER also
			// contains the uniform variables and constants as well as the
			// sampler declarations)
			sge::shader::vf_to_string<vf::format>(),
			fcppt::assign::make_container<sge::shader::variable_sequence>
				(sge::shader::variable(
					"mvp",
					sge::shader::variable_type::uniform,
					sge::shader::matrix(
						sge::renderer::matrix4::identity(),
						sge::shader::matrix_flags::projection)))
				(sge::shader::variable(
					"radius",
					sge::shader::variable_type::constant,
					static_cast<sge::renderer::scalar>(
						4)))
				// There's no "bool" support for shader variables, so we use an
				// integer here
				(sge::shader::variable(
					"enabled",
					sge::shader::variable_type::uniform,
					1))
				(sge::shader::variable(
					"camera",
					sge::shader::variable_type::uniform,
					sge::renderer::vector3()))
				(sge::shader::variable(
					"light_position",
					sge::shader::variable_type::uniform,
					sge::renderer::vector3::null())),
			// Two textures. They'll be assigned to a uniform variable index
			// automatically.
			fcppt::assign::make_container<sge::shader::sampler_sequence>
				(sge::shader::sampler(
					"normal_texture",
					normal_texture))
				(sge::shader::sampler(
					"color_texture",
					color_texture)))
			// We can specify more than one fragment and vertex shader here
			.vertex_shader(
				sge::config::media_path()
					/ FCPPT_TEXT("shaders")
					/ FCPPT_TEXT("cube")
					/ FCPPT_TEXT("vertex.glsl"))
			.fragment_shader(
				sge::config::media_path()
					/ FCPPT_TEXT("shaders")
					/ FCPPT_TEXT("cube")
					/ FCPPT_TEXT("fragment.glsl"))
			// The name is displayed in an error or warning message from the shader.
			.name(
				FCPPT_TEXT("Main shader")));

	bool enabled =
		true;

	fcppt::signal::scoped_connection const cb_enabled(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::e,
				std::tr1::bind(
					&toggle_bumpmapping,
					fcppt::ref(
						shader),
					fcppt::ref(
						enabled)))));

	sge::renderer::vertex_buffer_scoped_ptr const vb(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				vf::format,
				vf::format_part
			>(),
			// 6 sides, 2 triangles per side, 3 vertices (we don't use an
			// index buffer - overkill)
			sge::renderer::vertex_count(
				6u * 2u * 3u
			),
			sge::renderer::resource_flags_field::null()));

	fill_vb_with_cube(
		*vb);

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::update_duration(
				1.0f)));

	sge::timer::basic<sge::timer::clocks::standard> revolve_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			boost::chrono::seconds(
				10)));

	sge::font::text::drawer_3d font_drawer(
		sys.renderer(),
		sge::image::colors::red());

	sge::font::metrics_scoped_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
				/ FCPPT_TEXT("fonts")
				/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(
				30)));

	while(
		sys.window_system().poll())
	{
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				camera_timer));

		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::enable_alpha_blending = false)
				(sge::renderer::state::cull_mode::off)
				(sge::renderer::state::depth_func::less)
				(sge::renderer::state::draw_mode::fill)
				(sge::renderer::state::stencil_func::off));

		sge::renderer::active_target(
			sys.renderer()
		).clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black())
			.depth_buffer(
				1.f));

		sge::renderer::scoped_block const block(
			sys.renderer());

		{
			sge::shader::scoped scoped_shader(
				shader,
				sge::shader::activate_everything());

			sge::renderer::scoped_vertex_buffer const vb_context(
				sys.renderer(),
				*vb);

			shader.update_uniform(
				"mvp",
				sge::shader::matrix(
					sge::camera::matrix_conversion::world_projection(
						camera.coordinate_system(),
						camera.projection_matrix()),
					sge::shader::matrix_flags::projection));

			shader.update_uniform(
				"camera",
				camera.coordinate_system().position().get());

			sge::renderer::scalar const elapsed =
				sge::timer::elapsed_fractional<sge::renderer::scalar>(
					revolve_timer);

			sge::timer::reset_when_expired(
				revolve_timer);

			shader.update_uniform(
				"light_position",
				sge::renderer::vector3(
					std::sin(
						fcppt::math::twopi<sge::renderer::scalar>() *
						elapsed),
					0,
					std::cos(
						fcppt::math::twopi<sge::renderer::scalar>() *
						elapsed)));

			sys.renderer().render_nonindexed(
				sge::renderer::first_vertex(0u),
				sge::renderer::vertex_count(
					vb->size()),
				sge::renderer::nonindexed_primitive_type::triangle);
		}

		sge::font::text::draw(
			*font_metrics,
			font_drawer,
			SGE_FONT_TEXT_LIT("Press 'e' to toggle bump mapping"),
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::font::rect::dim>(
					sge::renderer::active_target(
						sys.renderer()
					).viewport().get().size()
				)
			),
			sge::font::text::align_h::left,
			sge::font::text::align_v::top,
			sge::font::text::flags::none);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
