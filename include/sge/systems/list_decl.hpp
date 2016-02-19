/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED

#include <sge/systems/list_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename Inits
>
class list
{
	FCPPT_NONASSIGNABLE(
		list
	);
public:
	explicit
	list(
		Inits const &
	);

	template<
		typename Param
	>
	list<
		typename boost::fusion::result_of::as_vector<
			typename boost::fusion::result_of::push_back<
				Inits,
				Param
			>::type
		>::type
	>
	operator()(
		Param const &
	) const;

	Inits const &
	get() const;
private:
	Inits inits_;
};

}
}

#endif
