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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_INITIALIZE_DEFAULTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_INITIALIZE_DEFAULTS_HPP_INCLUDED

#include <sge/sprite/defaults/fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

template<
	typename Parameters
>
class initialize_defaults
{
	FCPPT_NONASSIGNABLE(
		initialize_defaults
	);

	typedef typename Parameters::choices choices;
public:
	explicit
	initialize_defaults(
		Parameters &_parameters
	)
	:
		parameters_(
			_parameters
		)
	{
	}

	typedef void result_type;

	template<
		typename Role
	>
	typename boost::enable_if<
		typename sge::sprite::defaults<
			choices,
			typename Role::alias
		>::use,
		result_type
	>::type
	operator()() const
	{
		parameters_. template set<
			typename Role::alias
		>(
			sge::sprite::defaults<
				choices,
				typename Role::alias
			>::get()
		);
	}

	template<
		typename Role
	>
	typename boost::disable_if<
		typename sge::sprite::defaults<
			choices,
			typename Role::alias
		>::use,
		result_type
	>::type
	operator()() const
	{
	}
private:
	Parameters &parameters_;
};

}
}
}
}

#endif
