//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/channel8.hpp>
#include <sge/image/dim.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/store/basic.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/bgra8_format.hpp>
#include <sge/image2d/rgb8_format.hpp>
#include <sge/image2d/rgba8_format.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/store/bgra8.hpp>
#include <sge/image2d/store/rgb8.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <mizuiro/color/compare.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
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
	using
	source_store
	=
	sge::image::store::basic<
		Source
	>;

	source_store const source{
		typename source_store::dim(
			1U,
			1U
		),
		sge::image::pixel::mizuiro_type<
			typename Source::color_format
		>(
			_source
		)
	};

	using
	dest_store
	=
	sge::image::store::basic<
		Dest
	>;

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

	REQUIRE(
		mizuiro::color::compare(
			dest.view()[
				typename dest_store::view_type::dim(
					0U,
					0U
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

FCPPT_CATCH_BEGIN

TEST_CASE(
	"rgba_to_bgra",
	"[sge]"
)
{
	test_conversion<
		sge::image2d::rgba8_format,
		sge::image2d::bgra8_format
	>(
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		(sge::image::color::init::green() = channel8(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		(sge::image::color::init::alpha() = channel8(128)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);
}

FCPPT_CATCH_BEGIN

TEST_CASE(
	"rgb_to_rgba",
	"[sge]"
)
{
	test_conversion<
		sge::image2d::rgb8_format,
		sge::image2d::rgba8_format
	>(
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		(sge::image::color::init::green() = channel8(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		,
		(sge::image::color::init::red() = channel8(0))
		(sge::image::color::init::blue() = channel8(37)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		(sge::image::color::init::green() = channel8(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		(sge::image::color::init::alpha() = channel8(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);
}

FCPPT_CATCH_END
