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


#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_type.hpp>
/*
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/statement/if.hpp>
*/

// TODO: find out why the phoenix code does not work

namespace
{

class functor {
public:
	functor(
		sge::input::kc::type const code,
		sge::input::nullary_function const &fun)
	:
		code(code),
		fun(fun)
	{}

	void operator()(
		sge::input::key_pair const &p) const
	{
		if(p.key().code() == code)
			fun();
	}
private:
	sge::input::kc::type const code;
	sge::input::nullary_function const fun;
};

}

sge::input::callback const
sge::input::action(
	kc::type const code,
	nullary_function const &action)
{
	/*
	namespace phoenix = boost::phoenix;
	return phoenix::if_(
		phoenix::bind(
			&sge::input::key_type::code,
			phoenix::bind(
				&sge::input::key_pair::key,
				phoenix::arg_names::arg1
			)
		)
		== code
	)
	[
		action
	];*/

	return functor(
		code,
		action);
}
