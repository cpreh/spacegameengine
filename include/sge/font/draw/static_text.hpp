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


#ifndef SGE_FONT_DRAW_STATIC_TEXT_HPP_INCLUDED
#define SGE_FONT_DRAW_STATIC_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_fwd.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/set_matrices_fwd.hpp>
#include <sge/font/draw/set_states_fwd.hpp>
#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/font/draw/detail/static_text_impl_fwd.hpp>
#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace font
{
namespace draw
{

class static_text
{
	FCPPT_NONCOPYABLE(
		static_text
	);
public:
	SGE_FONT_DRAW_DETAIL_SYMBOL
	static_text(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sge::font::text_parameters const &,
		sge::font::vector const &,
		sge::image::color::any::object const &,
		sge::renderer::texture::emulate_srgb
	);

	SGE_FONT_DRAW_DETAIL_SYMBOL
	static_text(
		static_text &&
	);

	SGE_FONT_DRAW_DETAIL_SYMBOL
	static_text  &
	operator=(
		static_text &&
	);

	SGE_FONT_DRAW_DETAIL_SYMBOL
	~static_text();

	SGE_FONT_DRAW_DETAIL_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &
	) const;

	SGE_FONT_DRAW_DETAIL_SYMBOL
	void
	draw_advanced(
		sge::renderer::context::ffp &,
		sge::font::draw::set_matrices const &,
		sge::font::draw::set_states const &
	) const;

	SGE_FONT_DRAW_DETAIL_SYMBOL
	void
	pos(
		sge::font::vector const &
	);

	SGE_FONT_DRAW_DETAIL_SYMBOL
	void
	color(
		sge::image::color::any::object const &
	);

	SGE_FONT_DRAW_DETAIL_SYMBOL
	sge::font::vector
	pos() const;

	SGE_FONT_DRAW_DETAIL_SYMBOL
	sge::font::rect
	rect() const;

	SGE_FONT_DRAW_DETAIL_SYMBOL
	sge::font::dim
	logical_size() const;

	SGE_FONT_DRAW_DETAIL_SYMBOL
	sge::font::text const &
	text() const;
private:
	typedef
	fcppt::unique_ptr<
		sge::font::draw::detail::static_text_impl
	>
	impl_ptr;

	impl_ptr impl_;
};

}
}
}

#endif
