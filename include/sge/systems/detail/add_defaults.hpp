/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_DETAIL_ADD_DEFAULTS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ADD_DEFAULTS_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/list.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class add_defaults
{
	FCPPT_NONASSIGNABLE(
		add_defaults
	);
public:
	explicit
	add_defaults(
		sge::systems::detail::list &_result
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
		result_.insert(
			sge::systems::detail::any(
				typename sge::systems::detail::extract_parameter_type<
					Type
				>::type()
			)
		);
	}
private:
	sge::systems::detail::list &result_;
};

}
}
}

#endif
