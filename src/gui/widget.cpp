#include "widget.hpp"
#include "widgets/container.hpp"
#include "events/mouse_leave.hpp"
#include "events/mouse_move.hpp"
#include "manager.hpp"
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/rect_impl.hpp>

sge::gui::widget::widget(
	parent_data parent_data_,
	size_policy::type const size_policy_,
	point const &pos_,
	dim const &size_)
	:	parent_(parent_data_.parent_widget()),
	  manager_(parent_data_.parent_manager()),
		pos_(pos_),
		size_(size_),
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
	sge::cerr << "widget: size\n";
	
	sge::cerr << "widget: calling internal resize function\n";
	// then call the internal size method
	do_size(d);

	// is this widget a top level widget? then call the manager to resize the
	// underlying texture
	if (!parent_widget())
	{
		sge::cerr << "widget: size: calling manager's resize function\n";
		parent_manager().resize(*this,d);
	}

	// then invalidate the whole rect
	// sge::cerr << "widget: invalidating rectangle " << absolute_area() << "\n";
	// parent_manager().invalidate(absolute_area());
}

void sge::gui::widget::pos(point const &d)
{
	// is this widget a top level widget? then call the manager to reposition the
	// underlying sprite
	if (!parent_widget())
		parent_manager().reposition(*this,d);
	
	// then call the internal size method
	do_pos(d);
}

void sge::gui::widget::compile()
{
	sge::cerr << "widget: compiling\n";
	SGE_ASSERT_MESSAGE(!parent_widget(),SGE_TEXT("tried to compile a non top level widget, that's not possible"));
	sge::cerr << "widget: running do_compile\n";
	do_compile();

	// signal manager to recompile according to (new) size and position
	sge::cerr << "widget: running manager::compile\n";
	parent_manager().compile(*this);
	//sge::cerr << "widget: running manager::invalidate(" << absolute_area() << ")\n";
	//parent_manager().invalidate(absolute_area());
}

bool sge::gui::widget::is_container() const
{
	return dynamic_cast<widgets::container const *>(this);
}

sge::gui::widget *sge::gui::widget::recalculate_focus(point const &mouse_click)
{
	// pointer is no longer inside widget area
	if (!math::contains(absolute_area(),mouse_click))
	{
		cerr << "widget: mouse no longer inside widget, sending leave\n";
		process(events::mouse_leave());
		
		if (!parent_widget())
			return 0;

		return parent_widget()->recalculate_focus(mouse_click);
	}

	widget *const new_focus = do_recalculate_focus(mouse_click);
	if (new_focus == this)
	{
		cerr << "widget: focus hasn't changed, sending mouse_move\n";
		process(events::mouse_move(mouse_click));
	}
	return new_focus;
}
