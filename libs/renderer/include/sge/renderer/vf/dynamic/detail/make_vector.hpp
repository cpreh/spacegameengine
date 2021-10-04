//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_VECTOR_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_VECTOR_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/dynamic/element_count.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/vf/dynamic/detail/format_to_element.hpp>


namespace sge::renderer::vf::dynamic::detail
{

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements
>
sge::renderer::vf::dynamic::vector
make_vector()
{
	return
		sge::renderer::vf::dynamic::vector(
			sge::renderer::vf::dynamic::detail::format_to_element<
				Format
			>::value,
			sge::renderer::vf::dynamic::element_count(
				NumSubElements
			)
		);
}

}

#endif
