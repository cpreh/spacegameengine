#include "../../utility/ptr_delete_first.hpp"
#include "../../utility/ptr_find.hpp"
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/mouse_click.hpp>
#include <sge/gui/events/mouse_enter.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widget.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <sge/input/classification.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <sge/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("managers: mouse"),
	false);

sge::sprite::point const key_to_mouse_coords(sge::input::key_pair const &k)
{
	if (k.key().code() == sge::input::kc::mouse_x_axis)
		return sge::sprite::point(
			static_cast<sge::sprite::unit>(k.value()),
			static_cast<sge::sprite::unit>(0));
	return sge::sprite::point(
		static_cast<sge::sprite::unit>(0),
		static_cast<sge::sprite::unit>(k.value()));
}

bool active(sge::gui::widget const &w)
{
	switch (w.activation())
	{
		case sge::gui::activation_state::active:
			if (!w.parent_widget())
				return true;
			return active(*w.parent_widget());
		case sge::gui::activation_state::inactive:
			return false;
	}
	throw sge::exception(SGE_TEXT("missed an activation state"));
}
}

sge::gui::detail::managers::mouse::mouse(
	input::system_ptr const is,
	sge::image::loader_ptr const il,
	renderer::device_ptr const rend,
	skin &s)
:
	ic(
	  	is->register_callback(
	  		boost::bind(&mouse::input_callback,this,_1))),
	cursor_(
		sprite::defaults::pos_,
		texture::const_part_ptr(
			make_shared_ptr<
				texture::part_raw
			>(
				rend->create_texture(
				il->load(s.cursor_path())->view(),
				renderer::filter::linear,
				renderer::resource_flags::readable))),
		sprite::texture_dim,
		sprite::defaults::color_,
		static_cast<sprite::depth_type>(0)),
	//  cursor_click(point::null()),
	cursor_click(16,16),
	focus(0),
	dirty_(false)
{
}

void sge::gui::detail::managers::mouse::add(widget &w)
{
	// We only store top level widgets as "starting points" for our focus search
	if (!w.parent_widget())
		widgets.push_back(&w);
	
	// It could be the case that the newly added widget is below the cursor and should
	// thus get the focus, so we recalculate
	dirty_ = true;
}

void sge::gui::detail::managers::mouse::draw()
{
	if (dirty_)
	{
		recalculate_focus();
		dirty_ = false;
	}
}

void sge::gui::detail::managers::mouse::activation(
	widget &,
	activation_state::type)
{
	dirty_ = true;
}

sge::sprite::object const sge::gui::detail::managers::mouse::cursor() const
{
	return cursor_;
}

void sge::gui::detail::managers::mouse::remove(widget &w)
{
	// We've got a problem if
	// (a) the currently focused widget should be deleted, or...
	// (b) one of its children
	if (focus == &w || w.has_child(*focus))
	{
		// If so, we start at the focused widget and traverse the tree upwards until
		// we reach the widget's parent (it could be 0).
		widget *const parent = w.parent_widget();
		while (focus != parent)
		{
			focus->process(events::mouse_leave());
			focus = focus->parent_widget();
		}
	}

	// And if it's a top level widget, we have to delete it from our widgets list
	if (!w.parent_widget())
	{
		SGE_ASSERT(
			utility::ptr_find(widgets.begin(),widgets.end(),&w) != widgets.end());
		utility::ptr_delete_first(widgets,&w);
	}
}

void sge::gui::detail::managers::mouse::recalculate_focus()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in top level recalculate_focus"));

	point const click_point = structure_cast<point>(cursor_.pos()+cursor_click);

	if (focus)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("a widget currently has the focus, recalculating"));
			
		focus = recalculate_focus(*focus,click_point);
	}
	
	if (!focus)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << 
				SGE_TEXT("no widget currently has the focus, so letting it recalculate"));

		BOOST_FOREACH(widget &w,widgets)
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("checking if ") << w.screen_area() 
				        << SGE_TEXT(" contains ") << click_point);

			if (w.activation() == activation_state::active && 
			    math::contains(w.screen_area(),click_point))
			{
				w.process(events::mouse_enter(click_point));
				focus = recalculate_focus(w,click_point);
				return;
			}
		}
	}
}

void sge::gui::detail::managers::mouse::input_callback(
	input::key_pair const &k)
{
	if (input::is_mouse_axis(k.key().code()))
	{
		cursor_.pos() += key_to_mouse_coords(k);
		recalculate_focus();
		return;
	}

	if (!input::is_mouse_button(k.key().code()))
		return;

	if (!focus)
		return;

	focus->process(
		events::mouse_click(
			structure_cast<point>(
				cursor_.pos() + cursor_click),
			k));
}

sge::gui::widget *sge::gui::detail::managers::mouse::recalculate_focus(
	widget &w,
	point const &mouse_click)
{
	// Pointer is no longer inside widget area
	if (!math::contains(w.screen_area(),mouse_click) ||
	    !active(w))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("mouse no longer inside widget, sending leave"));

		w.process(events::mouse_leave());
		
		// Pointer is in "free space" now
		if (!w.parent_widget())
			return 0;

		// Recalculate from the parent on
		return recalculate_focus(*w.parent_widget(),mouse_click);
	}

	widget *const new_focus = do_recalculate_focus(w,mouse_click);

	if (new_focus == &w)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("focus hasn't changed, sending mouse_move"));
		w.process(events::mouse_move(mouse_click));
	}
	return new_focus;
}

sge::gui::widget *sge::gui::detail::managers::mouse::do_recalculate_focus(
	widget &w,
	point const &p)
{
	BOOST_FOREACH(widget &child,w.children())
	{
		if (child.activation() == activation_state::active && 
		    math::contains(child.screen_area(),p))
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("a child has the focus, sending enter and descending"));
			child.process(events::mouse_enter(p));
			return do_recalculate_focus(child,p);
		}
	}
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("no child has the focus, doing nothing"));
	return &w;
}
