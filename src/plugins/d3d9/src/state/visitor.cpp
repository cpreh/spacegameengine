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


#include <sge/d3d9/state/alpha_func.hpp>
#include <sge/d3d9/state/bool.hpp>
#include <sge/d3d9/state/color.hpp>
#include <sge/d3d9/state/cull_mode.hpp>
#include <sge/d3d9/state/depth_func.hpp>
#include <sge/d3d9/state/dest_blend_func.hpp>
#include <sge/d3d9/state/draw_mode.hpp>
#include <sge/d3d9/state/float.hpp>
#include <sge/d3d9/state/fog_mode.hpp>
#include <sge/d3d9/state/int.hpp>
#include <sge/d3d9/state/source_blend_func.hpp>
#include <sge/d3d9/state/stencil_func.hpp>
#include <sge/d3d9/state/stencil_op.hpp>
#include <sge/d3d9/state/uint.hpp>
#include <sge/d3d9/state/visitor.hpp>


sge::d3d9::state::visitor::visitor(
	state::parameters const &_parameters
)
:
	parameters_(_parameters)
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::int_::type const &_state
) const
{
	state::int_(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::uint::type const &_state
) const
{
	state::uint(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::float_::type const &_state
) const
{
	state::float_(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::bool_::type const &_state
) const
{
	state::bool_(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::color::type const &_state
) const
{
	state::color(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::cull_mode::type const _state
) const
{
	state::cull_mode(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::depth_func::type const _state
) const
{
	state::depth_func(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::stencil_func::type const _state
) const
{
	state::stencil_func(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::alpha_func::type const _state
) const
{
	state::alpha_func(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::fog_mode::type const _state
) const
{
	state::fog_mode(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::draw_mode::type const _state
) const
{
	state::draw_mode(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::source_blend_func::type const _state
) const
{
	state::source_blend_func(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::dest_blend_func::type const _state
) const
{
	state::dest_blend_func(
		parameters_,
		_state
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::stencil_op::type const &_state
) const
{
	state::stencil_op(
		parameters_,
		_state
	);
}
