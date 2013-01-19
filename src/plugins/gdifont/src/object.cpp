/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/gdifont/create_font.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/object.hpp>
#include <sge/gdifont/text.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sge::gdifont::object::object(
	sge::gdifont::device_context const &_device_context,
	sge::font::parameters const &_parameters
)
:
	sge::font::object(),
	device_context_(
		_device_context
	),
	font_(
		sge::gdifont::create_font(
			_parameters
		)
	)
{
}

sge::gdifont::object::~object()
{
}

sge::font::text_unique_ptr
sge::gdifont::object::create_text(
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	return
		sge::font::text_unique_ptr(
			fcppt::make_unique_ptr<
				sge::gdifont::text
			>(
				device_context_,
				font_.get(),
				_string,
				_text_parameters
			)
		);
}

sge::image::color::optional_format const
sge::gdifont::object::color_format() const
{
	// TODO: Support all formats
	return
		sge::image::color::optional_format(
			sge::image::color::format::a8
		);
}
