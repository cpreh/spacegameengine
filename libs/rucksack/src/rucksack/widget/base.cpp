//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/access_axis.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/impl/update_axis.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _value
)
{
	this->size(
		sge::rucksack::impl::update_axis(
			this->size(),
			_axis,
			_value
		)
	);
}

void
sge::rucksack::widget::base::position(
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _value
)
{
	this->position(
		sge::rucksack::impl::update_axis(
			this->position(),
			_axis,
			_value
		)
	);
}

sge::rucksack::scalar
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis
) const
{
	return
		sge::rucksack::access_axis(
			this->size(),
			_axis
		);
}

sge::rucksack::scalar
sge::rucksack::widget::base::position(
	sge::rucksack::axis const _axis
) const
{
	static_assert(
		sge::rucksack::vector::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value,
		""
	);

	return
		sge::rucksack::access_axis(
			this->position(),
			_axis
		);
}

sge::rucksack::widget::base::~base()
{
	fcppt::optional::maybe_void(
		parent_,
		[
			this
		](
			fcppt::reference<
				sge::rucksack::widget::base
			> const _parent
		)
		{
			_parent.get().child_destroyed(
				*this
			);
		}
	);
}

sge::rucksack::widget::base::base()
:
	parent_()
{
}

sge::rucksack::rect
sge::rucksack::widget::base::area() const
{
	return
		sge::rucksack::rect{
			this->position(),
			this->size()
		};
}

void
sge::rucksack::widget::base::parent(
	sge::rucksack::widget::optional_ref const &_parent
)
{
	parent_ =
		_parent;
}

sge::rucksack::widget::optional_ref
sge::rucksack::widget::base::parent() const
{
	return
		parent_;
}

void
sge::rucksack::widget::base::child_destroyed(
	sge::rucksack::widget::base &
)
{
}
