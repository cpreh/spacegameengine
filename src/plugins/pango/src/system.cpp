/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/charconv/system_fwd.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/object.hpp>
#include <sge/pango/system.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-fontmap.h>
#include <pango/pangoft2.h>
#include <fcppt/config/external_end.hpp>


sge::pango::system::system(
	sge::charconv::system &_charconv_system
)
:
	sge::font::system(),
	charconv_system_(
		_charconv_system
	),
	font_map_(
		::pango_ft2_font_map_new()
	),
	context_(
		::pango_font_map_create_context(
			font_map_.get()
		)
	)
{
}

sge::pango::system::~system()
{
}

sge::font::object_unique_ptr
sge::pango::system::create_font(
	sge::font::parameters const &_parameters
)
{
	return
		sge::font::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::pango::object
			>(
				fcppt::ref(
					charconv_system_
				),
				fcppt::ref(
					*context_
				),
				fcppt::cref(
					_parameters
				)
			)
		);
}
