//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED

#include <sge/renderer/vf/detail/raw_data_type.hpp>
#include <mizuiro/color/is_color.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/math/vector/is_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

template<
	typename T
>
inline
std::enable_if_t<
	fcppt::math::vector::is_vector<
		typename
		std::remove_const<
			T
		>::type
	>::value,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>
raw_data(
	T &_value
)
{
	return
		fcppt::cast::to_char_ptr<
			sge::renderer::vf::detail::raw_data_type<
				T
			>
		>(
			_value.storage().data()
		);
}

template<
	typename T
>
inline
std::enable_if_t<
	std::is_fundamental<
		T
	>::value,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>
raw_data(
	T &_value
)
{
	return
		fcppt::cast::to_char_ptr<
			sge::renderer::vf::detail::raw_data_type<
				T
			>
		>(
			&_value
		);
}

template<
	typename T
>
inline
std::enable_if_t<
	mizuiro::color::is_color<
		typename
		std::remove_const<
			T
		>::type
	>::value,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>
raw_data(
	T &_value
)
{
	return
		fcppt::cast::to_char_ptr<
			sge::renderer::vf::detail::raw_data_type<
				T
			>
		>(
			_value.data()
		);
}

}
}
}
}

#endif
