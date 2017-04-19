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


#include <sge/image/channel8.hpp>
#include <sge/image/dim.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image/store/basic.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/bgra8_format.hpp>
#include <sge/image2d/rgb8_format.hpp>
#include <sge/image2d/rgba8_format.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <mizuiro/color/compare.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::image::channel8
channel8(
	unsigned const _value
)
{
	return
		fcppt::cast::size<
			sge::image::channel8
		>(
			_value
		);
}

template<
	typename Source,
	typename Dest,
	typename ColorInitSource,
	typename ColorInitDest
>
void
test_conversion(
	ColorInitSource const &_source,
	ColorInitDest const &_dest
)
{
	typedef sge::image::store::basic<
		Source
	> source_store;

	source_store const source{
		typename source_store::dim(
			1u,
			1u
		),
		sge::image::pixel::mizuiro_type<
			typename Source::color_format
		>(
			_source
		)
	};

	typedef sge::image::store::basic<
		Dest
	> dest_store;

	dest_store const dest{
		source.size(),
		typename
		dest_store::init_function{
			[
				&source
			](
				typename
				dest_store::view_type const &_dest_view
			)
			{
				sge::image2d::algorithm::copy_and_convert(
					sge::image2d::view::const_object(
						source.const_wrapped_view()
					),
					sge::image2d::view::object(
						sge::image::view::wrap(
							_dest_view
						)
					),
					sge::image::algorithm::may_overlap::no,
					sge::image::algorithm::uninitialized::yes
				);
			}
		}
	};

	BOOST_REQUIRE(
		mizuiro::color::compare(
			dest.view()[
				typename dest_store::view_type::dim(
					0u,
					0u
				)
			],
			sge::image::pixel::mizuiro_type<
				typename Dest::color_format
			>(
				_dest
			),
			[](
				sge::image::channel8 const _a,
				sge::image::channel8 const _b
			)
			{
				return
					_a
					==
					_b;
			}
		)
	);
}

template<
	typename Source,
	typename Dest,
	typename ColorInit
>
void
test_conversion(
	ColorInit const &_value
)
{
	test_conversion<
		Source,
		Dest
	>(
		_value,
		_value
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	rgba_to_bgra
)
{
FCPPT_PP_POP_WARNING

	test_conversion<
		sge::image2d::rgba8_format,
		sge::image2d::bgra8_format
	>(
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37))
		(sge::image::color::init::green() = channel8(255))
		(sge::image::color::init::alpha() = channel8(128))
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	rgb_to_rgba
)
{
FCPPT_PP_POP_WARNING

	test_conversion<
		sge::image2d::rgb8_format,
		sge::image2d::rgba8_format
	>(
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37))
		(sge::image::color::init::green() = channel8(255))
		,
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37))
		(sge::image::color::init::green() = channel8(255))
		(sge::image::color::init::alpha() = channel8(255))
	);
}
