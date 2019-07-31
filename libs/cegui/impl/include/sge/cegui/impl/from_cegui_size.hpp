//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_FROM_CEGUI_SIZE_HPP_INCLUDED
#define SGE_CEGUI_IMPL_FROM_CEGUI_SIZE_HPP_INCLUDED

#include <fcppt/math/dim/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
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
fcppt::math::dim::static_<
	ValueType,
	2u
>
from_cegui_size(
	CEGUI::Size<
		ValueType
	> const &_size
)
{
	return
		fcppt::math::dim::static_<
			ValueType,
			2u
		>{
			_size.d_width,
			_size.d_height
		};
}

}
}
}

#endif
