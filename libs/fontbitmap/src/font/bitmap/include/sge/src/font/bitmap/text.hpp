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


#ifndef SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/line_height.hpp>
#include <sge/src/font/bitmap/rep.hpp>
#include <fcppt/noncopyable.hpp>


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
		sge::font::bitmap::line_height
	);

	~text()
	override;
private:
	void
	render(
		sge::font::view const &
	)
	override;

	sge::font::rect
	rect() const
	override;

	sge::font::dim
	logical_size() const
	override;

	sge::font::rect
	cursor_rect(
		sge::font::index
	) const
	override;

	sge::font::optional_index
	pos_to_index(
		sge::font::vector
	) const
	override;

	template<
		typename Function
	>
	void
	iterate(
		Function const &
	) const;

	sge::font::bitmap::line_height const line_height_;

	sge::font::align_h::variant const align_h_;

	sge::font::bitmap::rep const rep_;
};

}
}
}

#endif
