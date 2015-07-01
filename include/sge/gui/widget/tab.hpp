#ifndef SGE_GUI_WIDGET_TAB_HPP_INCLUDED
#define SGE_GUI_WIDGET_TAB_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/tab_fwd.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		tab
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	tab(
		sge::gui::context &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
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
