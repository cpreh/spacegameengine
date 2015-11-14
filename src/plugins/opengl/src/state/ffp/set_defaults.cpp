/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/set_defaults.hpp>
#include <sge/opengl/state/ffp/alpha_test/set.hpp>
#include <sge/opengl/state/ffp/clip_plane/set.hpp>
#include <sge/opengl/state/ffp/fog/set.hpp>
#include <sge/opengl/state/ffp/lighting/set.hpp>
#include <sge/opengl/state/ffp/lighting/light/set.hpp>
#include <sge/opengl/state/ffp/lighting/material/set.hpp>
#include <sge/opengl/state/ffp/misc/set.hpp>
#include <sge/opengl/state/ffp/sampler/set_defaults.hpp>
#include <sge/opengl/state/ffp/transform/set_defaults.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref.hpp>


void
sge::opengl::state::ffp::set_defaults(
	sge::opengl::context::object &_context
)
{
	sge::opengl::state::ffp::alpha_test::set(
		_context,
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref()
	);

	sge::opengl::state::ffp::clip_plane::set(
		_context,
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector()
	);

	sge::opengl::state::ffp::fog::set(
		_context,
		sge::renderer::state::ffp::fog::const_optional_object_ref()
	);

	sge::opengl::state::ffp::lighting::set(
		_context,
		sge::renderer::state::ffp::lighting::const_optional_object_ref()
	);

	sge::opengl::state::ffp::lighting::light::set(
		_context,
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector()
	);

	sge::opengl::state::ffp::lighting::material::set(
		_context,
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref()
	);

	sge::opengl::state::ffp::misc::set(
		_context,
		sge::renderer::state::ffp::misc::const_optional_object_ref()
	);

	sge::opengl::state::ffp::sampler::set_defaults(
		_context
	);

	sge::opengl::state::ffp::transform::set_defaults(
		_context
	);
}
