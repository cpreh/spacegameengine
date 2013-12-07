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


#include <sge/font/ascent.hpp>
#include <sge/font/descent.hpp>
#include <sge/font/description.hpp>
#include <sge/pango/make_description.hpp>
#include <sge/pango/convert/from_unit.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-font.h>
#include <pango/pango-fontmap.h>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::font::description const
sge::pango::make_description(
	PangoContext &_context,
	PangoLayout &_layout
)
{
	PangoFontDescription const *desc(
		::pango_layout_get_font_description(
			&_layout
		)
	);

	struct unref_metrics
	{
		void
		operator()(
			PangoFontMetrics *const _metrics
		)
		{
			::pango_font_metrics_unref(
				_metrics
			);
		}
	};

	typedef
	fcppt::scoped_ptr<
		PangoFontMetrics,
		unref_metrics
	>
	metrics_scoped_ptr;

	metrics_scoped_ptr const metrics(
		::pango_context_get_metrics(
			&_context,
			desc,
			nullptr
		)
	);

	return
		sge::font::description(
			sge::font::ascent(
				sge::pango::convert::from_unit(
					::pango_font_metrics_get_ascent(
						metrics.get()
					)
				)
			),
			sge::font::descent(
				sge::pango::convert::from_unit(
					::pango_font_metrics_get_descent(
						metrics.get()
					)
				)
			)
		);
}
