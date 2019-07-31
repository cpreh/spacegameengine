//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR3_HPP_INCLUDED
#define SGE_CEGUI_IMPL_FROM_CEGUI_VECTOR3_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

template<
	typename ValueType
>
fcppt::math::vector::static_<
	ValueType,
	3u
>
from_cegui_vector3(
	CEGUI::Vector3<
		ValueType
	> const &_size
)
{
	return
		fcppt::math::vector::static_<
			ValueType,
			3u
		>{
			_size.d_x,
			_size.d_y,
			_size.d_z
		};
}

}
}
}

#endif
