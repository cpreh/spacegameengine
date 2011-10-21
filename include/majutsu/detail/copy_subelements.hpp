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


#ifndef MAJUTSU_DETAIL_COPY_SUBELEMENTS_HPP_INCLUDED
#define MAJUTSU_DETAIL_COPY_SUBELEMENTS_HPP_INCLUDED

#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{
namespace detail
{

template<
	typename DestClass,
	typename SrcClass
>
class copy_subelements
{
	FCPPT_NONASSIGNABLE(
		copy_subelements
	);
public:
	explicit copy_subelements(
		DestClass &_dest,
		SrcClass const &_src
	)
	:
		dest_(_dest),
		src_(_src)
	{}

	typedef void result_type;

	template<
		typename Src
	>
	typename boost::enable_if<
		boost::mpl::contains<
			typename DestClass::memory_type::types,
			Src
		>,
		result_type
	>::type
	operator()(
		Src &
	) const
	{
		typedef typename Src::alias alias;

		dest_. template set<
			alias
		>(
			src_. template get<
				alias
			>()
		);
	}

	template<
		typename Src
	>
	typename boost::disable_if<
		boost::mpl::contains<
			typename DestClass::memory_type::types,
			Src
		>,
		result_type
	>::type
	operator()(
		Src &
	) const
	{
	}
private:
	DestClass &dest_;

	SrcClass const &src_;
};

}
}

#endif
