//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_POS_HPP_INCLUDED
#define SGE_RENDERER_VF_POS_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/pos_fwd.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>


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
struct pos
:
sge::renderer::vf::vector_base<
	Format,
	NumSubElements
>
{
	static_assert(
		fcppt::type_traits::is_float_or_double<
			Format
		>::value,
		"A vertex format pos can only be float or double"
	);

	static_assert(
		NumSubElements >= 2 && NumSubElements <= 4,
		"A vertex format pos must have between 2 and 4 elements"
	);

	typedef
	sge::renderer::vf::labels::pos
	label;
};

}
}
}

#endif
