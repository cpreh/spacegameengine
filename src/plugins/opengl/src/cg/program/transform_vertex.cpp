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


#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/opengl/cg/program/replace_index.hpp>
#include <sge/opengl/cg/program/transform_vertex.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>


sge::cg::program::source const
sge::opengl::cg::program::transform_vertex(
	sge::renderer::vertex::declaration const &,
	sge::cg::program::source const &_source
)
{
	return
		sge::cg::program::replace_extra(
			_source,
			sge::cg::program::replace_extra_callback(
				sge::opengl::cg::program::replace_index
			)
		);
}
