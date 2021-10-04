//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/detail/make_element.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/algorithm/map.hpp>


namespace sge::renderer::vf::dynamic::detail
{

template<
	typename Part
>
sge::renderer::vf::dynamic::part
make_part()
{
	return
		sge::renderer::vf::dynamic::part{
			fcppt::algorithm::map<
				sge::renderer::vf::dynamic::element_list
			>(
				typename
				Part::elements{},
				[](
					auto const &_tag
				)
				{
					FCPPT_USE(
						_tag
					);

					return
						sge::renderer::vf::dynamic::detail::make_element(
							fcppt::tag_type<
								decltype(
									_tag
								)
							>{}
						);
				}
			),
			fcppt::algorithm::map<
				sge::renderer::vf::dynamic::offset_list
			>(
				typename
				Part::offsets{},
				[](
					auto const &_tag
				)
				{
					FCPPT_USE(
						_tag
					);

					return
						sge::renderer::vf::dynamic::offset{
							fcppt::tag_type<
								decltype(
									_tag
								)
							>::value
						};
				}
			)
		};
}

}

#endif
