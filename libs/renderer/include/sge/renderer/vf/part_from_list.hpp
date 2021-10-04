//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PART_FROM_LIST_HPP_INCLUDED
#define SGE_RENDERER_VF_PART_FROM_LIST_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <fcppt/mpl/list/as.hpp>


namespace sge::renderer::vf
{

template<
	typename List
>
using
part_from_list
=
fcppt::mpl::list::as<
	sge::renderer::vf::part,
	List
>;

}

#endif
