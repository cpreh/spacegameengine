//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_TEXPOS_HPP_INCLUDED
#define SGE_RENDERER_VF_TEXPOS_HPP_INCLUDED

#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/texpos_fwd.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>


namespace sge::renderer::vf
{

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements,
	typename Index
>
struct texpos
:
sge::renderer::vf::vector_base<
	Format,
	NumSubElements
>
{
	static_assert(
		sge::renderer::is_valid_float_type<
			Format
		>::value,
		"Format must be float or double"
	);

	static_assert(
		NumSubElements >= 2
		&& NumSubElements <= 3,
		"NumSubElements mut be between 2 and 3"
	);

	using
	index
	=
	Index;

	using
	label
	=
	sge::renderer::vf::labels::texpos<
		Index::value
	>;
};

}

#endif
