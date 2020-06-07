//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VECTOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_VECTOR_BASE_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements
>
struct vector_base
{
	using
	subelement_type
	=
	Format;

	using
	packed_type
	=
	fcppt::math::vector::static_<
		Format,
		NumSubElements
	>;

	static
	sge::renderer::vf::element_count_type const num_subelements
		= NumSubElements;
};

}
}
}

#endif
