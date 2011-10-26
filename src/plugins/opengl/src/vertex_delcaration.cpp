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


#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


sge::opengl::vertex_declaration::vertex_declaration(
	opengl::context::object &_context,
	renderer::vf::dynamic::format const &_format
)
:
	format_(_format),
	parts_(),
	attribute_locations_()
{
	sge::renderer::vf::dynamic::part_list const &parts(
		format_.parts()
	);

	for(
		renderer::vf::dynamic::part_list::const_iterator it(
			parts.begin()
		);
		it != parts.end();
		++it
	)
		fcppt::container::ptr::push_back_unique_ptr(
			parts_,
			fcppt::make_unique_ptr<
				opengl::vf::part
			>(
				fcppt::ref(
					_context
				),
				*it,
				fcppt::ref(
					attribute_locations_
				)
			)
		);
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
		parts_.at(
			_part.get()
		);
}

sge::opengl::vf::attribute_location_container const &
sge::opengl::vertex_declaration::attribute_locations() const
{
	return attribute_locations_;
}
