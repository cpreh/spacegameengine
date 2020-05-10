//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COMPARE_ELEMENT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COMPARE_ELEMENT_HPP_INCLUDED

//#include <mizuiro/color/channel_proxy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
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
	std::enable_if_t<
		std::is_integral_v<
			T
		>,
		bool
	>
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
	std::enable_if_t<
		std::is_floating_point_v<
			T
		>,
		bool
	>
	operator()(
		T const _value1,
		T const _value2
	) const
	{
		T const epsilon{
			fcppt::literal<
				T
			>(
				0.00001
			)
		};

		return
			std::abs(
				_value1
				-
				_value2
			)
			<
			epsilon;
	}
};

}
}
}

#endif
