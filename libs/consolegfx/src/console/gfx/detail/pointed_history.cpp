//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/gfx/exception.hpp>
#include <sge/console/gfx/detail/pointed_history.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::console::gfx::detail::pointed_history::pointed_history(
	size_type const _limit
)
:
	container_(),
	limit_(
		_limit
	),
	point_(
		0U
	)
{
	if(
		limit_
		==
		0U
	)
	{
		throw
			sge::console::gfx::exception{
				FCPPT_TEXT("History size must be greater than 0.")
			};
	}
}

sge::console::gfx::detail::pointed_history::~pointed_history()
= default;

void
sge::console::gfx::detail::pointed_history::push_front(
	value_type &&_value
)
{
	container_.push_front(
		std::move(
			_value
		)
	);

	if(
		container_.size()
		>
		limit_
	)
	{
		container_.pop_back();
	}
}

void
sge::console::gfx::detail::pointed_history::up()
{
	if(
		point_
		!=
		container_.size() - 1U
	)
	{
		++point_;
	}
}

void
sge::console::gfx::detail::pointed_history::down()
{
	if(
		point_
		!=
		0U
	)
	{
		--point_;
	}
}

void
sge::console::gfx::detail::pointed_history::to_begin()
{
	point_ =
		0U;
}

void
sge::console::gfx::detail::pointed_history::to_end()
{
	point_ =
		container_.size() - 1U;
}

sge::console::gfx::detail::pointed_history::const_iterator
sge::console::gfx::detail::pointed_history::point() const
{
	return
		std::next(
			container_.begin(),
			static_cast<
				std::iterator_traits<
					const_iterator
				>::difference_type
			>(
				point_
			)
		);
}

sge::console::gfx::detail::pointed_history::const_iterator
sge::console::gfx::detail::pointed_history::end() const
{
	return
		container_.end();
}
