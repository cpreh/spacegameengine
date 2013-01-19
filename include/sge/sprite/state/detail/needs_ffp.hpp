/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <fcppt/config/external_end.hpp>


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
struct needs_ffp
{
private:
	template<
		typename Type
	>
	struct extract
	{
		typedef typename Type::needs_ffp type;
	};
public:
	typedef
	typename
	boost::mpl::fold<
		typename boost::mpl::transform<
			typename StateChoices::optional_elements,
			extract<
				boost::mpl::_1
			>
		>::type,
		boost::mpl::false_,
		boost::mpl::or_<
			boost::mpl::_1,
			boost::mpl::_2
		>
	>::type type;
};

}
}
}
}

#endif
