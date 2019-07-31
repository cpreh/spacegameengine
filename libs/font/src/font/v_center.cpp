//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/height.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/v_center.hpp>
#include <fcppt/literal.hpp>


sge::font::unit
sge::font::v_center(
	sge::font::height const _height,
	sge::font::unit const _size
)
{
	return
		(
			_height.get()
			-
			_size
		)
		/
		fcppt::literal<
			sge::font::unit
		>(
			2
		);
}
