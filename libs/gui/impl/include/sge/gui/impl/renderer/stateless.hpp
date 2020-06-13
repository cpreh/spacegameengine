//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <sge/renderer/device/core_fwd.hpp>
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
		sge::renderer::device::core &
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

	sge::renderer::device::core &renderer_;
};

}
}
}
}

#endif
