/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/cg/program/replace_index.hpp>
#include <sge/d3d9/cg/program/transform_vertex.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::cg::program::source const
sge::d3d9::cg::program::transform_vertex(
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::cg::program::source const &_source
)
{
	return
		sge::cg::program::replace_extra(
			_source,
			sge::cg::program::replace_extra_callback(
				std::bind(
					&sge::d3d9::cg::program::replace_index,
					dynamic_cast<
						sge::d3d9::vertex_declaration const &
					>(
						_vertex_declaration
					).texture_coordinates(),
					std::placeholders::_1
				)
			)
		);
}
