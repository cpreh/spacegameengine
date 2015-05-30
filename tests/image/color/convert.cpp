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


#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/is_convertible.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

static_assert(
	sge::image::color::is_convertible<
		sge::image::color::rgba8_format,
		sge::image::color::bgra8_format
	>::value,
	"rgba8 not convertible to bgra8"
);

static_assert(
	!sge::image::color::is_convertible<
		sge::image::color::a8_format,
		sge::image::color::bgra8_format
	>::value,
	"a8 should not be convertible to bgra8"
);

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	convert
)
{
FCPPT_PP_POP_WARNING

}
