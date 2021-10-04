//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MAKE_PART_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/mpl/list/index_of.hpp>


namespace sge::renderer::vf::dynamic
{

template<
	typename Format,
	typename Part
>
sge::renderer::vf::dynamic::part_index
make_part_index()
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::vf::dynamic::part_index,
			fcppt::cast::static_cast_fun
		>(
			fcppt::mpl::list::index_of<
				typename Format::parts,
				Part
			>::value
		);
}

}

#endif
