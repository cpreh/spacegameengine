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


#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/gdifont/create_font.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/make_metrics.hpp>
#include <sge/gdifont/object.hpp>
#include <sge/gdifont/text.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


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
	),
	metrics_(
		sge::gdifont::make_metrics(
			device_context_,
			font_.get_pointer()
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
		fcppt::unique_ptr_to_base<
			sge::font::text
		>(
			fcppt::make_unique_ptr<
				sge::gdifont::text
			>(
				device_context_,
				font_.get_pointer(),
				_string,
				_text_parameters
			)
		);
}

sge::image::color::optional_format
sge::gdifont::object::color_format() const
{
	// TODO: Support all formats
	return
		sge::image::color::optional_format(
			sge::image::color::format::a8
		);
}

sge::font::metrics
sge::gdifont::object::metrics() const
{
	return
		metrics_;
}
