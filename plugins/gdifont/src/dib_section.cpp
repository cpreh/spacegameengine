//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gdifont/create_dib_section.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/dib_section.hpp>
#include <sge/gdifont/get_bitmap.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/to_const.hpp>


sge::gdifont::dib_section::dib_section(
	sge::gdifont::device_context const &_device_context,
	sge::image2d::dim const &_size
)
:
	data_(
		nullptr
	),
	hbitmap_(
		sge::gdifont::create_dib_section(
			_device_context,
			_size,
			data_
		)
	),
	bitmap_(
		sge::gdifont::get_bitmap(
			hbitmap_.get_pointer()
		)
	)
{
}

sge::gdifont::dib_section::~dib_section()
{
}

sge::image2d::view::object const
sge::gdifont::dib_section::view()
{
	return
		sge::image2d::view::make(
			static_cast<
				sge::image::raw_pointer
			>(
				data_
			),
			sge::image2d::dim(
				static_cast<
					sge::image2d::dim::value_type
				>(
					bitmap_.bmWidth
				),
				static_cast<
					sge::image2d::dim::value_type
				>(
					bitmap_.bmHeight
				)
			),
			sge::image::color::format::a8,
			sge::image2d::pitch(
				bitmap_.bmWidthBytes - bitmap_.bmWidth
			)
		);
}

sge::image2d::view::const_object const
sge::gdifont::dib_section::const_view() const
{
	return
		sge::image2d::view::to_const(
			const_cast<
				sge::gdifont::dib_section &
			>(
				*this
			).view()
		);
}

HBITMAP
sge::gdifont::dib_section::handle()
{
	return
		hbitmap_.get_pointer();
}
