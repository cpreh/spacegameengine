/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_GUI_IMPL_RENDERER_STATELESS_HPP_INCLUDED
#define SGE_GUI_IMPL_RENDERER_STATELESS_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace renderer
{

class stateless
:
	public sge::gui::renderer::base
{
	FCPPT_NONCOPYABLE(
		stateless
	);
public:
	explicit
	stateless(
		sge::renderer::device::ffp &
	);

	~stateless()
	override;
private:
	void
	fill_rect(
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::image::color::any::object const &
	)
	override;

	void
	draw_image(
		sge::renderer::context::ffp &,
		sge::texture::part const &,
		sge::rucksack::vector
	)
	override;

	void
	draw_image_repeat(
		sge::renderer::context::ffp &,
		sge::texture::part const &,
		sge::rucksack::rect
	)
	override;

	void
	draw_static_text(
		sge::renderer::context::ffp &,
		sge::font::draw::static_text const &
	)
	override;

	sge::renderer::device::ffp &renderer_;
};

}
}
}
}

#endif
