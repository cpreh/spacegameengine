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
#include <sge/d3d9/vf/create.hpp>
#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/d3d9/vf/convert/role.hpp>
#include <sge/d3d9/vf/convert/type.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


sge::d3d9::vf::element_vector const
sge::d3d9::vf::create(
	sge::renderer::vf::dynamic::format const &_format,
	sge::renderer::vf::vertex_size const _texture_coordinates
)
{
	sge::d3d9::vf::element_vector vertex_elements;

	WORD stream(
		0
	);

	typedef std::map<
		D3DDECLUSAGE,
		unsigned
	> usage_count_map;

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
		usage_count_map usage_counts;

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
		{
			sge::renderer::vf::dynamic::ordered_element const &ordered_element(
				*element_it
			);

			D3DDECLUSAGE const usage(
				sge::d3d9::vf::convert::role(
					ordered_element.element()
				)
			);

			D3DVERTEXELEMENT9 const new_elem =
			{
				stream, // Stream
				static_cast<
					WORD
				>(
					ordered_element.offset()
				), // Offset
				static_cast<
					BYTE
				>(
					sge::d3d9::vf::convert::type(
						ordered_element.element()
					)
				), // Type
				D3DDECLMETHOD_DEFAULT,
				static_cast<
					BYTE
				>(
					usage
				),
				static_cast<
					BYTE
				>(
					usage_counts[
						usage
					]++
				)
			};

			vertex_elements.push_back(
				new_elem
			);
		}

		++stream;
	}

	D3DVERTEXELEMENT9 const end_token = D3DDECL_END();

	vertex_elements.push_back(
		end_token
	);

	return
		vertex_elements;
}
