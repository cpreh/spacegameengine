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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COMPARE_ELEMENT_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COMPARE_ELEMENT_HPP_INCLUDED

//#include <mizuiro/color/channel_proxy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <cmath>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace algorithm
{

struct compare_element
{
/*
	// TODO: Create a decay function that decays const channel_proxies
	template<
		typename Pointer1,
		typename ValueType1,
		typename ChannelAccess1,
		typename Pointer2,
		typename ValueType2,
		typename ChannelAccess2
	>
	bool
	operator()(
		mizuiro::color::channel_proxy<
			Pointer1,
			ValueType1,
			ChannelAccess1
		> const _proxy1,
		mizuiro::color::channel_proxy<
			Pointer2,
			ValueType2,
			ChannelAccess2
		> const _proxy2
	) const
	{
		return
			(*this)(
				_proxy1.get(),
				_proxy2.get()
			);
	}*/

	template<
		typename T
	>
	typename
	boost::enable_if<
		std::is_integral<
			T
		>,
		bool
	>::type
	operator()(
		T const _value1,
		T const _value2
	) const
	{
		return
			_value1
			==
			_value2;
	}

	template<
		typename T
	>
	typename
	boost::enable_if<
		std::is_floating_point<
			T
		>,
		bool
	>::type
	operator()(
		T const _value1,
		T const _value2
	) const
	{
		return
			std::abs(
				_value1
				-
				_value2
			)
			<
			fcppt::literal<
				T
			>(
				0.00001
			);
	}
};

}
}
}

#endif
