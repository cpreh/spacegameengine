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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED

#include <sge/image/color/invalid_convert.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/function.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/rgb_to_srgb.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/srgb_to_rgb.hpp>
#include <sge/src/image/color/dynamic/view/color_format.hpp>
#include <mizuiro/color/conversion/rgb_to_srgb.hpp>
#include <mizuiro/color/conversion/same_to_same.hpp>
#include <mizuiro/color/conversion/srgb_to_rgb.hpp>
#include <mizuiro/color/format/same_spaces.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename SourceFormat,
	typename DestFormat
>
inline
typename
boost::enable_if<
	mizuiro::color::format::same_spaces<
		typename
		SourceFormat::color_format,
		typename
		DestFormat::color_format
	>,
	sge::image::color::dynamic::algorithm::cac::function<
		SourceFormat,
		DestFormat
	>
>::type
choose(
	SourceFormat const &,
	DestFormat const &
)
{
	return
		&mizuiro::color::conversion::same_to_same<
			typename DestFormat::color_format,
			sge::image::color::dynamic::algorithm::cac::source<
				SourceFormat
			>
		>;
}

template<
	typename SourceFormat,
	typename DestFormat
>
inline
typename
boost::enable_if<
	sge::image::color::dynamic::algorithm::cac::rgb_to_srgb<
		SourceFormat,
		DestFormat
	>,
	sge::image::color::dynamic::algorithm::cac::function<
		SourceFormat,
		DestFormat
	>
>::type
choose(
	SourceFormat const &,
	DestFormat const &
)
{
	return
		&mizuiro::color::conversion::rgb_to_srgb<
			typename
			DestFormat::color_format,
			sge::image::color::dynamic::algorithm::cac::source<
				SourceFormat
			>
		>;
}

template<
	typename SourceFormat,
	typename DestFormat
>
inline
typename
boost::enable_if<
	sge::image::color::dynamic::algorithm::cac::srgb_to_rgb<
		SourceFormat,
		DestFormat
	>,
	sge::image::color::dynamic::algorithm::cac::function<
		SourceFormat,
		DestFormat
	>
>::type
choose(
	SourceFormat const &,
	DestFormat const &
)
{
	return
		&mizuiro::color::conversion::srgb_to_rgb<
			typename
			DestFormat::color_format,
			sge::image::color::dynamic::algorithm::cac::source<
				SourceFormat
			>
		>;
}

template<
	typename SourceFormat,
	typename DestFormat
>
inline
typename
boost::disable_if<
	boost::mpl::or_<
		mizuiro::color::format::same_spaces<
			typename
			SourceFormat::color_format,
			typename
			DestFormat::color_format
		>,
		sge::image::color::dynamic::algorithm::cac::rgb_to_srgb<
			SourceFormat,
			DestFormat
		>,
		sge::image::color::dynamic::algorithm::cac::srgb_to_rgb<
			SourceFormat,
			DestFormat
		>
	>,
	sge::image::color::dynamic::algorithm::cac::function<
		SourceFormat,
		DestFormat
	>
>::type
choose(
	SourceFormat const &_source,
	DestFormat const &_dest
)
{
	throw
		sge::image::color::invalid_convert{
			sge::image::color::dynamic::view::color_format(
				_source
			).color_format,
			sge::image::color::dynamic::view::color_format(
				_dest
			).color_format
		};
}

}
}
}
}
}
}

#endif
