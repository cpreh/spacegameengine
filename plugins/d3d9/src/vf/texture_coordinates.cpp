//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/texture_coordinates.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <fcppt/variant/holds_type.hpp>


sge::d3d9::vf::texture_coordinate_count const
sge::d3d9::vf::texture_coordinates(
	sge::renderer::vf::dynamic::format const &_format
)
{
	sge::d3d9::vf::texture_coordinate_count result(
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
