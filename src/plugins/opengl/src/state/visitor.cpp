/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/state/alpha_func.hpp>
#include <sge/opengl/state/bool.hpp>
#include <sge/opengl/state/color.hpp>
#include <sge/opengl/state/cull_mode.hpp>
#include <sge/opengl/state/depth_func.hpp>
#include <sge/opengl/state/dest_blend_func.hpp>
#include <sge/opengl/state/draw_mode.hpp>
#include <sge/opengl/state/float.hpp>
#include <sge/opengl/state/fog_mode.hpp>
#include <sge/opengl/state/int.hpp>
#include <sge/opengl/state/parameters_fwd.hpp>
#include <sge/opengl/state/source_blend_func.hpp>
#include <sge/opengl/state/stencil_func.hpp>
#include <sge/opengl/state/stencil_op.hpp>
#include <sge/opengl/state/uint.hpp>
#include <sge/opengl/state/visitor.hpp>
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/uint.hpp>


sge::opengl::state::visitor::visitor(
	state::parameters const &_parameters
)
:
	parameters_(
		_parameters
	)
{
}

sge::opengl::state::visitor::~visitor()
{
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::int_::type const &_state
) const
{
	state::int_(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::uint::type const &_state
) const
{
	state::uint(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::float_::type const &_state
) const
{
	state::float_(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::bool_::type const &_state
) const
{
	state::bool_(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::color::type const &_state
) const
{
	state::color(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::stencil_op::type const &_state
) const
{
	state::stencil_op(
		parameters_,
		_state
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::cull_mode::type const _mode
) const
{
	state::cull_mode(
		parameters_,
		_mode
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::depth_func::type const _func
) const
{
	state::depth_func(
		parameters_,
		_func
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::stencil_func::type const _func
) const
{
	state::stencil_func(
		parameters_,
		_func
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::alpha_func::type const _func
) const
{
	state::alpha_func(
		parameters_,
		_func
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::fog_mode::type const _mode
) const
{
	state::fog_mode(
		parameters_,
		_mode
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::draw_mode::type const _mode
) const
{
	state::draw_mode(
		parameters_,
		_mode
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::source_blend_func::type const _func
) const
{
	state::source_blend_func(
		parameters_,
		_func
	);
}

sge::opengl::state::visitor::result_type
sge::opengl::state::visitor::operator()(
	renderer::state::dest_blend_func::type const _func
) const
{
	state::dest_blend_func(
		parameters_,
		_func
	);
}
