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


#include <sge/d3d9/vf/texture_coordinates.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <fcppt/variant/holds_type.hpp>


sge::renderer::vf::vertex_size
sge::d3d9::vf::texture_coordinates(
	sge::renderer::vf::dynamic::format const &_format
)
{
	sge::renderer::vf::vertex_size result(
		0u
	);

	sge::renderer::vf::dynamic::part_list const &parts(
		_format.parts()
	);

	for(
		sge::renderer::vf::dynamic::part_list::const_iterator part_it(
			parts.begin()
		);
		part_it != parts.end();
		++part_it
	)
	{
		sge::renderer::vf::dynamic::ordered_element_list const &elements(
				part_it->elements()
		);

		for(
			sge::renderer::vf::dynamic::ordered_element_list::const_iterator element_it(
				elements.begin()
			);
			element_it != elements.end();
			++element_it
		)
			if(
				fcppt::variant::holds_type<
					sge::renderer::vf::dynamic::texpos
				>(
					element_it->element().info()
				)
			)
				++result;
	}

	return result;
}
