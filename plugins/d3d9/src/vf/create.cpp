//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/create.hpp>
#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/index.hpp>
#include <sge/d3d9/vf/convert/role.hpp>
#include <sge/d3d9/vf/convert/type.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/cast/size.hpp>


sge::d3d9::vf::element_vector
sge::d3d9::vf::create(
	sge::renderer::vf::dynamic::format const &_format,
	sge::d3d9::vf::texture_coordinate_count const _texture_coordinates
)
{
	sge::d3d9::vf::element_vector vertex_elements;

	WORD stream(
		0
	);

	// TODO: map_concat with counted range
	for(
		sge::renderer::vf::dynamic::part const &part
		:
		_format.parts()
	)
	{
		for(
			sge::renderer::vf::dynamic::ordered_element const &ordered_element
			:
			part.elements()
		)
		{
			D3DDECLUSAGE const usage(
				sge::d3d9::vf::convert::role(
					ordered_element.element()
				)
			);

			D3DVERTEXELEMENT9 const new_elem =
			{
				stream,
				fcppt::cast::size<
					WORD
				>(
					ordered_element.offset().get()
				),
				fcppt::cast::size<
					BYTE
				>(
					sge::d3d9::vf::convert::type(
						ordered_element.element()
					)
				),
				D3DDECLMETHOD_DEFAULT,
				fcppt::cast::size<
					BYTE
				>(
					usage
				),
				sge::d3d9::vf::convert::index(
					ordered_element.element(),
					_texture_coordinates
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
