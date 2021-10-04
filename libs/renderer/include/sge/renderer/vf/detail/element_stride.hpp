//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_ELEMENT_STRIDE_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_ELEMENT_STRIDE_HPP_INCLUDED

#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vf::detail
{

template<
	typename T
>
using
element_stride
=
std::integral_constant<
	sge::renderer::vf::vertex_size,
	sizeof(typename T::subelement_type)
	* T::num_subelements
>;

}

#endif
