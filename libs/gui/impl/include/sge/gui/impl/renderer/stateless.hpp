//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_IMPL_RENDERER_STATELESS_HPP_INCLUDED
#define SGE_GUI_IMPL_RENDERER_STATELESS_HPP_INCLUDED

#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::gui::impl::renderer
{

class stateless
:
	public sge::gui::renderer::base
{
	FCPPT_NONMOVABLE(
		stateless
	);
public:
	explicit
	stateless(
		sge::renderer::device::core_ref
	);

	~stateless()
	override;
private:
	void
	fill_rect(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::rucksack::rect const &,
		sge::image::color::any::object const &
	)
	override;

	void
	draw_image(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::texture::part const &,
		sge::rucksack::vector const &
	)
	override;

	void
	draw_image_repeat(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::texture::part const &,
		sge::rucksack::rect const &
	)
	override;

	void
	draw_static_text(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::font::draw::static_text const &
	)
	override;

	sge::renderer::device::core_ref const renderer_;
};

}

#endif
