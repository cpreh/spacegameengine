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


#include "../state_visitor.hpp"
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::int_::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::uint::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::float_::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::bool_::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::color::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::cull_mode::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::depth_func::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::stencil_func::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::alpha_func::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::fog_mode::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::draw_mode::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::source_blend_func::type
) const
{
}

sge::d3d9::state_visitor::result_type
sge::d3d9::state_visitor::operator()(
	sge::renderer::state::dest_blend_func::type
) const
{
}

