//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_RENDERER_BASE_HPP_INCLUDED
#define SGE_GUI_RENDERER_BASE_HPP_INCLUDED

#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace renderer
{

class base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	SGE_GUI_DETAIL_SYMBOL
	base();
public:
	SGE_GUI_DETAIL_SYMBOL
	virtual
	~base();

	virtual
	void
	fill_rect(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::rucksack::rect const &,
		sge::image::color::any::object const &
	) = 0;

	virtual
	void
	draw_image(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::texture::part const &,
		sge::rucksack::vector const &
	) = 0;

	virtual
	void
	draw_image_repeat(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::texture::part const &,
		sge::rucksack::rect const &
	) = 0;

	virtual
	void
	draw_static_text(
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::font::draw::static_text const &
	) = 0;
};

}
}
}

#endif
