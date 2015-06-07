/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_INIT_ONE_OPTION_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_INIT_ONE_OPTION_HPP_INCLUDED

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
class init_one_option
{
	FCPPT_NONASSIGNABLE(
		init_one_option
	);
public:
	typedef
	sge::sprite::state::detail::options_class<
		StateChoices
	>
	options_class;

	explicit
	init_one_option(
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
