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


#ifndef SGE_PANGO_TEXT_HPP_INCLUDED
#define SGE_PANGO_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/pango/extents.hpp>
#include <sge/pango/no_multi_line.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class text
:
	public sge::font::text
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	text(
		PangoLayout &,
		sge::font::string const &,
		sge::font::text_parameters const &
	);

	~text()
	override;
private:
	void
	render(
		sge::font::view const &
	)
	override;

	sge::font::rect const
	rect() const
	override;

	sge::font::dim const
	logical_size() const;

	sge::font::rect const
	cursor_rect(
		sge::font::index
	) const
	override;

	sge::font::optional_index const
	pos_to_index(
		sge::font::vector
	) const
	override;

	sge::pango::pango_layout_unique_ptr const layout_;

	sge::pango::no_multi_line const no_multi_line_;

	sge::pango::extents const extents_;
};

}
}

#endif
