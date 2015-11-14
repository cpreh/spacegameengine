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


#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>


sge::opengl::vertex_declaration::vertex_declaration(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::declaration_parameters const &_parameters
)
:
	sge::renderer::vertex::declaration(),
	format_(
		_parameters.format()
	),
	parts_(
		fcppt::algorithm::map<
			part_container
		>(
			format_.parts(),
			[
				&_context
			](
				sge::renderer::vf::dynamic::part const &_part
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::opengl::vf::part
					>(
						_context,
						_part
					);

			}
		)
	)
{
}

sge::opengl::vertex_declaration::~vertex_declaration()
{
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vertex_declaration::format_part(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		format_.parts().at(
			_part.get()
		);
}

sge::opengl::vf::part const &
sge::opengl::vertex_declaration::gl_format_part(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		*parts_.at(
			_part.get()
		);
}
