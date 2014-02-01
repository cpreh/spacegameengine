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


#ifndef SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED

#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/line_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace bitmap
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
		sge::font::bitmap::char_map const &,
		sge::font::string const &,
		sge::font::text_parameters const &,
		sge::font::unit line_height
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

	typedef
	boost::ptr_vector<
		sge::font::bitmap::line
	>
	line_vector;

	line_vector lines_;

	sge::font::rect rect_;

	sge::font::unit const line_height_;

	sge::font::align_h::variant const align_h_;
};

}
}
}

#endif
