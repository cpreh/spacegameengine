#include <sge/gui/impl/shrink_rect.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/math/box/shrink.hpp>


sge::rucksack::rect const
sge::gui::impl::shrink_rect(
	sge::rucksack::rect const _rect,
	sge::rucksack::scalar const _scalar
)
{
	return
		fcppt::math::box::shrink(
			_rect,
			sge::rucksack::vector(
				_scalar,
				_scalar
			)
		);
}
