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
#include <sge/d3d9/vf/convert/index_visitor.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>


sge::d3d9::vf::convert::index_visitor::index_visitor(
	sge::renderer::vf::vertex_size const _texture_coordinates
)
:
	texture_coordinates_(
		_texture_coordinates
	)
{
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::pos const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::normal const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::color const &
) const
{
	return
		static_cast<
			BYTE
		>(
			0
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &_texpos
) const
{
	return
		static_cast<
			BYTE
		>(
			_texpos.index()
		);
}

sge::d3d9::vf::convert::index_visitor::result_type
sge::d3d9::vf::convert::index_visitor::operator()(
	sge::renderer::vf::dynamic::extra const &_extra
) const
{
	return
		static_cast<
			BYTE
		>(
			_extra.index()
			+
			texture_coordinates_
		);
}
