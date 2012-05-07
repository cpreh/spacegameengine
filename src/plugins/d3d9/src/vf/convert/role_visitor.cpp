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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/role_visitor.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>


sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(
	sge::renderer::vf::dynamic::pos const &
) const
{
	return D3DDECLUSAGE_POSITION;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(
	sge::renderer::vf::dynamic::normal const &
) const
{
	return D3DDECLUSAGE_NORMAL;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(
	sge::renderer::vf::dynamic::color const &
) const
{
	return D3DDECLUSAGE_COLOR;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &
) const
{
	return D3DDECLUSAGE_TEXCOORD;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(
	sge::renderer::vf::dynamic::extra const &
) const
{
	return D3DDECLUSAGE_TEXCOORD;
}
