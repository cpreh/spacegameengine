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


#include <sge/font/exception.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/view.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/dib_section.hpp>
#include <sge/gdifont/make_flags.hpp>
#include <sge/gdifont/render.hpp>
#include <sge/gdifont/set_bk_color.hpp>
#include <sge/gdifont/set_text_color.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <sge/gdifont/text.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/a8_format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/algorithm/copy.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/element_base.hpp>
#include <sge/image2d/view/size.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>


sge::gdifont::text::text(
	sge::gdifont::device_context const &_device_context,
	HFONT const _hfont,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
:
	sge::font::text(),
	device_context_(
		_device_context
	),
	hfont_(
		_hfont
	),
	string_(
		_string
	),
	render_flags_(
		sge::gdifont::make_flags(
			_text_parameters
		)
	),
	rect_(
		sge::gdifont::calc_rect(
			device_context_,
			string_,
			_text_parameters.max_width(),
			render_flags_
		)
	)
{
}

sge::gdifont::text::~text()
{
}

void
sge::gdifont::text::render(
	sge::font::view const &_view
)
{
	typedef sge::image2d::view::element_base<
		sge::image::color::a8_format,
		mizuiro::nonconst_tag
	>::type a8_view;

	if(
		!fcppt::variant::holds_type<
			a8_view
		>(
			_view.get()
		)
	)
		throw sge::font::exception(
			FCPPT_TEXT("Only a8 formats are currently supported in gdifont!")
		);

	sge::image2d::dim const view_size(
		sge::image2d::view::size(
			_view
		)
	);

	sge::gdifont::dib_section dib_section(
		device_context_,
		view_size
	);

	sge::gdifont::scoped_select const select_font(
		device_context_,
		hfont_
	);

	sge::gdifont::scoped_select const select_dib(
		device_context_,
		dib_section.handle()
	);

	sge::gdifont::set_bk_color(
		device_context_,
		RGB(0, 0, 0)
	);

	sge::gdifont::set_text_color(
		device_context_,
		RGB(255, 255, 255)
	);
	
	sge::gdifont::render(
		device_context_,
		string_,
		rect_.size(),
		render_flags_
	);

	sge::image2d::algorithm::copy(
		dib_section.view(),
		_view,
		sge::image::algorithm::may_overlap::no
	);
}

sge::font::rect const
sge::gdifont::text::rect()
{
	return rect_;
}
