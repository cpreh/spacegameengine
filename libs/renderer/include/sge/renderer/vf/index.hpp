//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/index_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vf
{

template<
	sge::renderer::vf::index_type Index
>
using
index
=
std::integral_constant<
	sge::renderer::vf::index_type,
	Index
>;

}

#endif
