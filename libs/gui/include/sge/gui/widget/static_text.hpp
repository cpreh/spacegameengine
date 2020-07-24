//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_STATIC_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGET_STATIC_TEXT_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/static_text_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class static_text
:
	public sge::gui::widget::base
{
	FCPPT_NONMOVABLE(
		static_text
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	static_text(
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::font::string const &,
		sge::gui::text_color const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~static_text()
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

	sge::font::draw::static_text static_text_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif

