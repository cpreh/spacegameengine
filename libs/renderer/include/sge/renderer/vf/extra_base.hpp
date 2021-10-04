//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_EXTRA_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_EXTRA_BASE_HPP_INCLUDED

#include <sge/renderer/vf/labels/extra.hpp>


namespace sge::renderer::vf
{

template<
	typename Base,
	typename Index
>
struct extra_base
:
	Base
{
	using
	index
	=
	Index;

	using
	label
	=
	sge::renderer::vf::labels::extra<
		Index::value
	>;
};

}

#endif
