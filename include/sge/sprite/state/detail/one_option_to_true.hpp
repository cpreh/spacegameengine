/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_STATE_DETAIL_ONE_OPTION_TO_TRUE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_ONE_OPTION_TO_TRUE_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
class one_option_to_true
{
	FCPPT_NONASSIGNABLE(
		one_option_to_true
	);
public:
	typedef typename sge::sprite::state::detail::options_class<
		StateChoices
	>::type options_class;

	explicit
	one_option_to_true(
		options_class &_result
	)
	:
		result_(
			_result
		)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()() const
	{
		result_. template set<
			typename Type::role
		>(
			true
		);
	}
private:
	options_class &result_;
};

}
}
}
}

#endif
