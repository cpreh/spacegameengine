//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_IMAGE_HPP_INCLUDED
#define SGE_GUI_WIDGET_IMAGE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/image_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class image
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		image
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	image(
		sge::gui::style::base const &,
		sge::texture::part const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~image()
	override;

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

	sge::gui::style::base const &style_;

	sge::texture::part const &texture_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
