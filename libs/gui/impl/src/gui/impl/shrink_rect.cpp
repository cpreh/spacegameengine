//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/impl/shrink_rect.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/math/box/shrink.hpp>
#include <fcppt/math/vector/fill.hpp>


sge::rucksack::rect
sge::gui::impl::shrink_rect(
	sge::rucksack::rect const &_rect,
	sge::rucksack::scalar const _scalar
)
{
	return
		fcppt::math::box::shrink(
			_rect,
			fcppt::math::vector::fill<
				sge::rucksack::vector
			>(
				_scalar
			)
		);
}
