//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_NORMAL_HPP_INCLUDED
#define SGE_RENDERER_VF_NORMAL_HPP_INCLUDED

#include <sge/renderer/vf/normal_fwd.hpp>
#include <sge/renderer/vf/vector3_base.hpp>
#include <sge/renderer/vf/labels/normal.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format
>
struct normal
:
sge::renderer::vf::vector3_base<
	Format
>
{
	static_assert(
		fcppt::type_traits::is_float_or_double<
			Format
		>::value,
		"Format needs to be float or double"
	);

	typedef
	sge::renderer::vf::labels::normal
	label;
};

}
}
}

#endif
