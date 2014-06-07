/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/ascent.hpp>
#include <sge/font/descent.hpp>
#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/unit.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/get_text_metrics.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/make_metrics.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <fcppt/cast/size.hpp>


sge::font::metrics const
sge::gdifont::make_metrics(
	sge::gdifont::device_context const &_device_context,
	HFONT const _font
)
{
	sge::gdifont::scoped_select const selection(
		_device_context,
		_font
	);

	TEXTMETRIC const metric(
		sge::gdifont::get_text_metrics(
			_device_context
		)
	);

	return
		sge::font::metrics(
			sge::font::ascent(
				fcppt::cast::size<
					sge::font::unit
				>(
					metric.tmAscent
				)
			),
			sge::font::descent(
				fcppt::cast::size<
					sge::font::unit
				>(
					metric.tmDescent
				)
			),
			sge::font::height(
				fcppt::cast::size<
					sge::font::unit
				>(
					metric.tmHeight
				)
			)
		);
}
