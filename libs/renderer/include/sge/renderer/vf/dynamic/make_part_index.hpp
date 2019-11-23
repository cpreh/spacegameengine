//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/contains.hpp>
#include <metal/list/find.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

template<
	typename Format,
	typename Part
>
sge::renderer::vf::dynamic::part_index
make_part_index()
{
	static_assert(
		metal::contains<
			typename Format::parts,
			Part
		>::value
	);

	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::vf::dynamic::part_index,
			fcppt::cast::static_cast_fun
		>(
			metal::find<
				typename Format::parts,
				Part
			>::value
		);
}

}
}
}
}

#endif
