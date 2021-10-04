//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_NORMAL_HPP_INCLUDED
#define SGE_RENDERER_VF_NORMAL_HPP_INCLUDED

#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/renderer/vf/normal_fwd.hpp>
#include <sge/renderer/vf/vector3_base.hpp>
#include <sge/renderer/vf/labels/normal.hpp>


namespace sge::renderer::vf
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
		sge::renderer::is_valid_float_type<
			Format
		>::value,
		"Format needs to be float or double"
	);

	using
	label
	=
	sge::renderer::vf::labels::normal;
};

}

#endif
