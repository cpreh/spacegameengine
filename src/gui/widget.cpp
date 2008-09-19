#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/manager.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/rect_impl.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("widget"));
}

sge::gui::widget::widget(
	parent_data parent_data_,
	size_policy_t const &size_policy_)
	:	parent_(parent_data_.parent_widget()),
	  manager_(parent_data_.parent_manager()),
		size_policy_(size_policy_)
{
	if (parent_widget())
		parent_widget()->add_child(*this);
	else
		parent_manager().add(*this);
}

sge::gui::widget::~widget()
{
	if (parent_widget())
		parent_widget()->remove_child(*this);
	else
		parent_manager().remove(*this);
}

sge::gui::rect const sge::gui::widget::absolute_area() const
{
	return rect(pos(), size());
}

sge::gui::rect const sge::gui::widget::relative_area() const
{
	return rect(point(static_cast<unit>(0),static_cast<unit>(0)), size());
}

void sge::gui::widget::size(dim const &d)
{
	do_size(d);
	compile();
}

void sge::gui::widget::pos(point const &d)
{
	do_pos(d);

	// is this widget a top level widget? then call the manager to reposition the
	// underlying sprite
	if (!parent_widget())
		parent_manager().reposition(*this,d);
}

void sge::gui::widget::compile()
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "compiling");
	if (parent_widget())
	{
		parent_widget()->compile();
		return;
	}
	
	SGE_LOG_DEBUG(mylogger,log::_1 << "running do_compile");
	set_size_raw(size_hint());
	do_compile();

	// signal manager to recompile according to (new) size and position
	SGE_LOG_DEBUG(mylogger,log::_1 << "running manager::compile");
	parent_manager().compile(*this);
}

bool sge::gui::widget::is_container() const
{
	return dynamic_cast<widgets::container const *>(this);
}

void sge::gui::widget::process(events::invalid_area const &e)
{
	manager().skin()->draw(*this,e);
}

sge::gui::widget *sge::gui::widget::recalculate_focus(point const &mouse_click)
{
	// pointer is no longer inside widget area
	if (!math::contains(absolute_area(),mouse_click))
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << "mouse no longer inside widget, sending leave");
		process(events::mouse_leave());
		
		if (!parent_widget())
			return 0;

		return parent_widget()->recalculate_focus(mouse_click);
	}

	widget *const new_focus = do_recalculate_focus(mouse_click);
	if (new_focus == this)
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << "focus hasn't changed, sending mouse_move");
		process(events::mouse_move(mouse_click));
	}
	return new_focus;
}
