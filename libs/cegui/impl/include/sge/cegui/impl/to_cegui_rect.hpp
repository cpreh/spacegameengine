//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_TO_CEGUI_RECT_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TO_CEGUI_RECT_HPP_INCLUDED

#include <fcppt/math/box/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <fcppt/config/external_end.hpp>


namespace sge::cegui::impl
{

template<
	typename ValueType
>
CEGUI::Rect<
	ValueType
>
to_cegui_rect(
	fcppt::math::box::rect<
		ValueType
	> const &_container
)
{
	return
		CEGUI::Rect<
			ValueType
		>(
			_container.left(),
			_container.top(),
			_container.right(),
			_container.bottom()
		);
}

}

#endif
