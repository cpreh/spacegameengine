//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_IMAGE_HPP_INCLUDED
#define SGE_GUI_WIDGET_IMAGE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/image_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::gui::widget
{

class image
:
	public sge::gui::widget::base
{
	FCPPT_NONMOVABLE(
		image
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	image(
		sge::gui::style::const_reference,
		sge::texture::const_part_ref
	);

	SGE_GUI_DETAIL_SYMBOL
	~image()
	override;

	[[nodiscard]]
	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sge::gui::style::const_reference const style_;

	sge::texture::const_part_ref const texture_;

	sge::rucksack::widget::dummy layout_;
};

}

#endif
