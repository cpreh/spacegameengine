/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <fcppt/nonassignable.hpp>

namespace
{

class functor
{
	FCPPT_NONASSIGNABLE(
		functor
	)
public:
	functor(
		sge::input::keyboard::key_code::type,
		sge::input::nullary_function const &
	);

	void
	operator()(
		sge::input::keyboard::key_event const &
	) const;
private:
	sge::input::keyboard::key_code::type const code_;

	sge::input::nullary_function const fun_;
};

}

sge::input::keyboard::key_callback const
sge::input::keyboard::action(
	keyboard::key_code::type const _code,
	input::nullary_function const &_action
)
{
	return
		::functor(
			_code,
			_action
		);
}

namespace
{

functor::functor(
	sge::input::keyboard::key_code::type const _code,
	sge::input::nullary_function const &_fun
)
:
	code_(_code),
	fun_(_fun)
{}

void
functor::operator()(
	sge::input::keyboard::key_event const &_event
) const
{
	if(
		_event.pressed()
		&& _event.key().code() == code_
	)
		fun_();
}

}
