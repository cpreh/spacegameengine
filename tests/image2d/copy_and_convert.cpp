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


#include <sge/image/color/argb8.hpp>
#include <sge/image/color/channel8.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/store.hpp>
#include <sge/image2d/argb8.hpp>
#include <sge/image2d/rgba8.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <mizuiro/image/view.hpp>
#include <mizuiro/color/operators/equal.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <boost/test/unit_test.hpp>

namespace
{

sge::image::color::channel8
channel8(
	unsigned const _value
)
{
	return
		static_cast<
			sge::image::color::channel8
		>(
			_value
		);
}

}

BOOST_AUTO_TEST_CASE(
	rgba_to_argb
)
{
	typedef sge::image2d::rgba8 source_store;

	source_store source(
		sge::image2d::rgba8::dim_type(
			1,
			1	
		)
	);

	typedef source_store::view_type source_view_type;

	source_view_type const source_view(
		source.view()
	);

	source_view[
		source_view_type::dim_type(
			0,
			0
		)
	] =
		sge::image::color::rgba8(
			(sge::image::color::init::red = channel8(0))
			(sge::image::color::init::blue = channel8(37))
			(sge::image::color::init::green = channel8(255))
			(sge::image::color::init::alpha = channel8(128))
		);
	
	typedef sge::image2d::argb8 dest_store;

	dest_store dest(
		source.dim()
	);

	typedef dest_store::view_type dest_view_type;

	dest_view_type dest_view(
		dest.view()
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::const_object(
			source_store::const_view_type(
				source_view
			)
		),
		sge::image2d::view::object(
			dest_view
		)
	);

	BOOST_REQUIRE(
		dest_view[
			dest_view_type::dim_type(
				0,
				0
			)
		]
		==
		sge::image::color::argb8(
			(sge::image::color::init::red = channel8(0))
			(sge::image::color::init::blue = channel8(37))
			(sge::image::color::init::green = channel8(255))
			(sge::image::color::init::alpha = channel8(128))
		)
	);
}
