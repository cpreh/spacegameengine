//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_TAB_HPP_INCLUDED
#define SGE_GUI_WIDGET_TAB_HPP_INCLUDED

#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/tab_fwd.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class tab
:
	public sge::gui::widget::box_container
{
	FCPPT_NONMOVABLE(
		tab
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	tab(
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::gui::widget::reference_name_vector const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~tab()
	override;
private:
	sge::gui::widget::unique_ptr_vector top_buttons_;

	sge::gui::widget::box_container top_buttons_box_;
};

}
}
}

#endif
