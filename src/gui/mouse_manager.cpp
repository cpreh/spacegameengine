#include "mouse_manager.hpp"

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("mouse_manager"),true);

sge::sprite::point const key_to_mouse_coords(sge::input::key_pair const &k)
{
	if (k.key().code() == sge::input::kc::mouse_x_axis)
		return sge::sprite::point(static_cast<sge::sprite::unit>(k.value()),static_cast<sge::sprite::unit>(0));
	return sge::sprite::point(static_cast<sge::sprite::unit>(0),static_cast<sge::sprite::unit>(k.value()));
}
}

sge::gui::detail::mouse_manager::mouse_manager(
	input::system_ptr const is,
	image::loader_ptr const il,
	renderer::device_ptr const rend,
	skin &s)
	: ic(
	  	is->register_callback(
	  		boost::bind(&mouse_manager::input_callback,this,_1))),
	  cursor(
			sprite::defaults::pos_,
			texture::part_ptr(
				new texture::part_raw(
					rend->create_texture(
					il->load(s.cursor_path())->view(),
					renderer::linear_filter,
					renderer::resource_flags::readable))),
			sprite::texture_dim,
			sprite::defaults::color_,
			static_cast<sge::sprite::depth_type>(0)),
	  cursor_click(point::null()),
		focus(0)
{
}

void sge::gui::detail::mouse_manager::add_widget(widget &w)
{
	widgets.push_back(&w);
}

void sge::gui::detail::mouse_manager::remove_widget(widget &w)
{
	ptr_delete_first(widgets,&w);
}

void sge::gui::detail::mouse_manager::input_callback(
	input::key_pair const &k)
{
	if (input::is_mouse_axis(k.key().code()))
	{
		cursor.pos() += key_to_mouse_coords(k);
		recalculate_focus();
		return;
	}

	if (!input::is_mouse_button(k.key().code()))
		return;

	if (!mouse_focus)
		return;

	mouse_focus->process(
		events::mouse_click(
			math::structure_cast<unit>(
				cursor.pos()+cursor_click),
			k));
}

void sge::gui::detail::mouse_manager::recalculate_focus()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in top level recalculate_mouse_focus"));

	point const click_point = math::structure_cast<unit>(cursor.pos()+cursor_click);

	if (mouse_focus)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("a widget currently has the focus, recalculating"));
			
		mouse_focus = mouse_focus->recalculate_focus(click_point);
	}
	
	if (!mouse_focus)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << 
				SGE_TEXT("no widget currently has the focus, so letting it recalculate"));

		BOOST_FOREACH(widget &w,widgets)
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("checking if ") << w.absolute_area() 
				        << SGE_TEXT(" contains ") << click_point);

			if (math::contains(w.absolute_area(),click_point))
			{
				w.process(events::mouse_enter(click_point));
				mouse_focus = w.recalculate_focus(click_point);
				return;
			}
		}
	}
}

sge::gui::widget *sge::gui::detail::mouse_manager::recalculate_focus(
	widget &w,
	point const &mouse_click)
{
	// pointer is no longer inside widget area
	if (!math::contains(w.absolute_area(),mouse_click))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("mouse no longer inside widget, sending leave"));

		w.process(events::mouse_leave());
		
		if (!w.parent_widget())
			return 0;

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

sge::gui::widget *sge::gui::detail::mouse_manager::do_recalculate_focus(
	widget &w,
	point const &mouse_click)
{
	return w.is_container() 
			? do_recalculate_focus(static_cast<widgets::container &>(w),mouse_click)
			: &w;
}

sge::gui::widget *sge::gui::detail::mouse_manager::do_recalculate_focus(
	widgets::container &w,
	point const &p)
{
	BOOST_FOREACH(widget &child,w.children())
	{
		if (math::contains(child.absolute_area(),p))
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("a child has the focus, sending enter"));
			child.process(events::mouse_enter(p));
			return do_recalculate_focus(w,p);
		}
	}
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("no child has the focus, doing nothing"));
	return this;
}
