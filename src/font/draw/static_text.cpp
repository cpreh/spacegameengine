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


#include <sge/font/object_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/src/font/draw/detail/static_text_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sge::font::draw::static_text::static_text(
	sge::renderer::device &_device,
	sge::font::object &_font,
	sge::font::string const &_string,
	sge::font::text_parameters const &_parameters,
	sge::font::rect const &_rect,
	sge::image::color::any::object const &_color
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::font::draw::detail::static_text_impl
		>(
			fcppt::ref(
				_device
			),
			fcppt::ref(
				_font
			),
			fcppt::cref(
				_parameters
			)
		)
	)
{
	impl_->rect(
		_rect
	);

	impl_->string(
		_string
	);

	impl_->color(
		_color
	);

	impl_->rebuild_texture();
}

sge::font::draw::static_text::~static_text()
{
}

void
sge::font::draw::static_text::draw(
	sge::renderer::context::object &_context
)
{
	impl_->draw(
		_context
	);
}

void
sge::font::draw::static_text::string(
	sge::font::string const &_text
)
{
	impl_->string(
		_text
	);

	impl_->rebuild_texture();
}

void
sge::font::draw::static_text::rect(
	sge::font::rect const &_rect
)
{
	impl_->rect(
		_rect
	);

	impl_->rebuild_texture();
}

void
sge::font::draw::static_text::color(
	sge::image::color::any::object const &_color
)
{
	impl_->color(
		_color
	);
}
