//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/detail/make_part.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/algorithm/map.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Format
>
sge::renderer::vf::dynamic::format
make_format()
{
	return
		sge::renderer::vf::dynamic::format{
			fcppt::algorithm::map<
				sge::renderer::vf::dynamic::part_list
			>(
				typename
				Format::parts{},
				[](
					auto const &_tag
				)
				{
					FCPPT_USE(
						_tag
					);

					return
						sge::renderer::vf::dynamic::detail::make_part<
							fcppt::tag_type<
								decltype(
									_tag
								)
							>
						>();
				}
			)
		};
}

}
}
}
}

#endif
