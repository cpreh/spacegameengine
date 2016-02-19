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


#ifndef SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED

#include <sge/renderer/vf/detail/raw_data_type.hpp>
#include <mizuiro/color/is_color.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/math/vector/is_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
typename
boost::enable_if<
	fcppt::math::vector::is_vector<
		typename
		std::remove_const<
			T
		>::type
	>,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>::type
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
typename
boost::enable_if<
	std::is_fundamental<
		T
	>,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>::type
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
typename
boost::enable_if<
	mizuiro::color::is_color<
		typename
		std::remove_const<
			T
		>::type
	>,
	sge::renderer::vf::detail::raw_data_type<
		T
	>
>::type
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
