#include "../grid.hpp"
#include "../grid_entry.hpp"
#include "../circle.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/container/field_impl.hpp>
#include <sge/structure_cast.hpp>

sge::cell::grid::grid(
	collision::rect const &rect_)
:
	rect_(rect_),
	field_(
		field_type::dim_type(
			static_cast<field_type::size_type>(rect_.w() / 10),
			static_cast<field_type::size_type>(rect_.h() / 10)
		)
	)
{}

sge::cell::grid::~grid()
{}

sge::cell::field_type &
sge::cell::grid::field()
{
	return field_;
}

sge::cell::grid::pos_type const
sge::cell::grid::pos() const
{
	return rect_.pos();
}

sge::cell::grid::dim_type const
sge::cell::grid::cell_size() const
{
	return rect_.dim()
	/ structure_cast<
		dim_type
	>(
		field_.dim()
	);
}
