/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/renderer/is_epsilon_equal.hpp>
#include <sge/renderer/state/any.hpp>
#include <sge/renderer/state/apply.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/set.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

template<typename T>
typename
boost::disable_if
<
	boost::is_floating_point<T>,
	bool
>::type
compare_maybe_with_epsilon(
	T const a,
	T const b)
{
	return a == b;
}

template<typename T>
typename
boost::enable_if
<
	boost::is_floating_point<T>,
	bool
>::type
compare_maybe_with_epsilon(
	T const a,
	T const b)
{
	return sge::renderer::is_epsilon_equal(a,b);
}

bool
state_unchanged(
	sge::renderer::state::any const &,
	sge::renderer::state::list const &
);

class compare_state_visitor
{
	FCPPT_NONASSIGNABLE(
		compare_state_visitor
	);
public:
	explicit compare_state_visitor(
		sge::renderer::state::any const &_state
	);

	typedef bool result_type;

	template<
		typename Type,
		typename State
	>
	result_type
	operator()(
		sge::renderer::state::var<
			Type,
			State
		> const &
	) const;

	template<
		typename Type
	>
	result_type
	operator()(
		Type const &
	) const;
private:
	sge::renderer::state::any const &state_;
};

}

void
sge::renderer::state::apply(
	state::list &_current_states,
	state::list const &_new_states,
	state::apply_callback const &_callback
)
{
	sge::renderer::state::set const &set(
		_new_states.values()
	);

	for(
		sge::renderer::state::set::const_iterator it(
			set.begin()
		);
		it != set.end();
		++it
	)
	{
		if(
			::state_unchanged(
				*it,
				_current_states
			)
		)
			continue;

		_current_states.overwrite(
			*it
		);

		_callback(
			*it
		);
	}
}


namespace
{

bool
state_unchanged(
	sge::renderer::state::any const &_state,
	sge::renderer::state::list const &_list
)
{
	sge::renderer::state::set const &state_list(
		_list.values()
	);

	sge::renderer::state::set::const_iterator const it(
		state_list.find(
			_state
		)
	);

	if(
		it == state_list.end()
	)
		return false;

	return
		fcppt::variant::apply_unary(
			::compare_state_visitor(
				_state
			),
			*it
		);
}

compare_state_visitor::compare_state_visitor(
	sge::renderer::state::any const &_state
)
:
	state_(_state)
{
}

template<
	typename Type,
	typename State
>
compare_state_visitor::result_type
compare_state_visitor::operator()(
	sge::renderer::state::var<
		Type,
		State
	> const &_other
) const
{
	return
		::compare_maybe_with_epsilon(
			state_.get<
				sge::renderer::state::var<
					Type,
					State
				>
			>().value(),
			_other.value()
		);
}

template<
	typename Type
>
compare_state_visitor::result_type
compare_state_visitor::operator()(
	Type const &_other
) const
{
	return
		state_.get<
			Type
		>()
		==
		_other;
}

}
