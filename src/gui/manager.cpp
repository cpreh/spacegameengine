#include <sge/gui/manager.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/events/mouse_enter.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/events/mouse_click.hpp>
#include <sge/media.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/assert.hpp>
#include <sge/iostream.hpp>
#include <sge/sprite/object.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("manager"));
}

sge::gui::manager::widget_data::widget_data(
	widget &w,
	renderer::texture_ptr texture,
	sprite::object const &spr)
	: ptr(&w),
		texture(texture),
		spr(spr)
{
}

sge::gui::manager::manager(
	renderer::device_ptr const rend,
	image::loader_ptr const il,
	input::system_ptr const is,
	font::system_ptr const fs)
	: rend(rend),
	  il(il),
	  is(is),
		fs(fs),
		standard_font_(
			fs->create_font(sge::media_path()/SGE_TEXT("fonts/default.ttf"),15)),
		ic(is->register_callback(boost::bind(&manager::input_callback,this,_1))),
		ss(rend),
		cursor(
			sprite::defaults::pos_,
			texture::part_ptr(
				new texture::part_raw(
					rend->create_texture(
					il->load_image(media_path()/SGE_TEXT("mainskin/cursor_pressed.png"))->view(),
					renderer::linear_filter,
					renderer::resource_flags::readable))),
			sprite::texture_dim,
			sprite::defaults::color_,
			static_cast<sge::sprite::depth_type>(0)),
		// top left
		cursor_click(),
		keyboard_focus(0),
		mouse_focus(0),
		skin_(new skins::standard())
{
}

void sge::gui::manager::reposition(widget &w,point const &d)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "repositioning sprite to " << d);
	// just reset sprite position
	get_data(w).spr.pos() = math::structure_cast<sprite::unit>(d);
}

void sge::gui::manager::resize(widget &w,dim const &d)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "resizing widget from " << w.size() << " to " << d);

	// TODO: if the widget is shrunk, you could fill the extra space with
	// transparent pixels so you don't have to create a whole new texture. if it
	// is enlarged, you could create a texture which is too large so subsequent
	// resize operations won't eat much performance
	widget_data &wd = get_data(w);

	renderer::texture_ptr software_texture(new renderer::texture_software(
		math::structure_cast<renderer::texture::dim_type::value_type>(d),
		renderer::color_format::rgba8));

	renderer::texture_ptr hardware_texture = rend->create_texture(
		math::structure_cast<renderer::texture::dim_type::value_type>(d),
		renderer::color_format::rgba8,
		renderer::linear_filter,
		renderer::resource_flags::dynamic);
	
	// NOTE: the sprite::object has to get a texture convertible to
	// sge::ogl::texture, so we give it hardware_texture below. the sprite_texture
	// serves as a canvas for the widgets and we pass it here
	wd.texture.reset(new renderer::texture_rw(software_texture,hardware_texture));
							
	wd.spr = sprite::object(
				sprite::point(math::structure_cast<sprite::unit>(w.pos())),
				texture::part_ptr(new texture::part_raw(hardware_texture)),
				sprite::dim(math::structure_cast<sprite::unit>(d)),
				sprite::defaults::color_,
				static_cast<sprite::depth_type>(1)
			);
	
	//SGE_LOG_DEBUG(mylogger,log::_1 << "resized widget, now locking it and let it draw itself");
	invalidate(rect(w.pos(),d));
}

sge::gui::manager::widget_data &sge::gui::manager::get_data(widget &w)
{
	widget_container::iterator wi = get_data_iterator(w);
	SGE_ASSERT_MESSAGE(wi != widgets_.end(),SGE_TEXT("widget is not a top level widget"));
	return *wi;
}

sge::gui::manager::widget_container::iterator sge::gui::manager::get_data_iterator(widget &w)
{
	return std::find_if(widgets_.begin(),widgets_.end(),
			boost::lambda::bind(&widget_data::ptr,boost::lambda::_1) == 
				boost::lambda::constant(&w));
}

void sge::gui::manager::invalidate(rect const &r)
{
	dirt_.push_back(r);
}


sge::gui::manager::widget_data &sge::gui::manager::parent_widget_data(widget &w)
{
	// top level widget? then forward to get_data
	if (!w.parent_widget())
		return get_data(w);
	return parent_widget_data(*w.parent_widget());
}

void sge::gui::manager::add(widget &w)
{
	widgets_.push_back(widget_data(w,renderer::texture_ptr(),sprite::object()));
}

void sge::gui::manager::recalculate_mouse_focus()
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "in top level recalculate_mouse_focus");

	point const click_point = math::structure_cast<unit>(cursor.pos()+cursor_click);

	if (mouse_focus)
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << "a widget currently has the focus, so letting it recalculate");
		mouse_focus = mouse_focus->recalculate_focus(click_point);
	}
	
	if (!mouse_focus)
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << "no widget currently has the focus, so letting it recalculate");
		BOOST_FOREACH(widget_data &wd,widgets_)
		{
			if (math::contains(wd.spr.get_rect(),click_point))
			{
				wd.ptr->process(events::mouse_enter(click_point));
				mouse_focus = wd.ptr->recalculate_focus(click_point);
				return;
			}
		}
	}

	SGE_LOG_DEBUG(mylogger,log::_1 << "finished recalculating focus");
}

void sge::gui::manager::compile(widget &w)
{
	SGE_ASSERT_MESSAGE(
		get_data_iterator(w) != widgets_.end(),
		SGE_TEXT("tried to compile a non toplevel widget"));

	resize(w,w.size());
	reposition(w,w.pos());

	recalculate_mouse_focus();
}

void sge::gui::manager::redraw_dirt()
{
	// calculate bounding rect of all dirt rects
	rect const bound = sge::math::bounding<unit>(dirt_.begin(),dirt_.end());
	SGE_LOG_DEBUG(mylogger,log::_1 << "bounding rect of all dirty regions is " << bound << "");
	dirt_.clear();
	
	SGE_LOG_DEBUG(mylogger,
		log::_1 << "invalidate called for rect " << bound << ", checking intersections");
	// if rects intersect, pass event on to top level widgets
	BOOST_FOREACH(widget_data &wd,widgets_)
	{
		if (math::intersects(wd.ptr->absolute_area(),bound))
		{
			SGE_LOG_DEBUG(mylogger,
				log::_1 << "got an intersection with area " << wd.ptr->absolute_area());

			// if it intersects, lock the whole intersection
			rect const widget_area  = wd.ptr->absolute_area();
			rect const is = math::intersection(widget_area,bound);

			SGE_LOG_DEBUG(mylogger,log::_1 << "intersection is " << is);

			// we have to convert the global intersection rect to a local one so we
			// can lock the texture
			rect const is_local(
				is.left()-widget_area.left(),
				is.top()-widget_area.top(),
				is.right()-widget_area.left(),
				is.bottom()-widget_area.top());

			SGE_LOG_DEBUG(mylogger,log::_1 << "locking " << is_local << " and sending invalid_area event");

			renderer::scoped_texture_lock lock_(
				renderer::make_scoped_lock(
					wd.texture,
					math::structure_cast<renderer::lock_rect::value_type>(is_local),
					renderer::lock_flags::readwrite
				));

			wd.ptr->process(
				events::invalid_area(
					canvas(
						lock_.value(),
						wd.ptr->absolute_area(),
						is)));

			SGE_LOG_DEBUG(mylogger,log::_1 << "invalid_area sent, now unlocking");
		}
	}
	SGE_LOG_DEBUG(mylogger,log::_1 << "checking intersections completed");
}

void sge::gui::manager::draw()
{
	if (!dirt_.empty())
		redraw_dirt();

	sprite::system::container sprites;
	BOOST_FOREACH(widget_data &w,widgets_)
		sprites.push_back(w.spr);
	sprites.push_back(cursor);
	ss.render(sprites.begin(),sprites.end());
}

void sge::gui::manager::remove(widget &w)
{
	// FIXME: is_container = ugly
	bool recalculate = 
		mouse_focus == &w || 
		(w.is_container() && dynamic_cast<widgets::container &>(w).has_child(*mouse_focus));
	
	if (recalculate)
		mouse_focus = w.parent_widget();

	widgets_.erase(std::find_if(widgets_.begin(),widgets_.end(),
		boost::lambda::bind(&widget_data::ptr,boost::lambda::_1) == 
			boost::lambda::constant(&w)));
	
	if (recalculate)
		recalculate_mouse_focus();
}

namespace
{
sge::sprite::point const key_to_mouse_coords(sge::input::key_pair const &k)
{
	if (k.key().code() == sge::input::kc::mouse_x_axis)
		return sge::sprite::point(static_cast<sge::sprite::unit>(k.value()),static_cast<sge::sprite::unit>(0));
	return sge::sprite::point(static_cast<sge::sprite::unit>(0),static_cast<sge::sprite::unit>(k.value()));
}
}

void sge::gui::manager::input_callback(input::key_pair const &k)
{
	if (input::is_mouse_axis(k.key().code()))
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << "mouse move " << key_to_mouse_coords(k));
		cursor.pos() += key_to_mouse_coords(k);
		recalculate_mouse_focus();
		return;
	}

	if (input::is_mouse_button(k.key().code()) && !math::almost_zero(k.value()))
	{
		if (!mouse_focus)
			return;

		mouse_focus->process(
			events::mouse_click(
				math::structure_cast<unit>(cursor.pos()+cursor_click),
				k.key().code()));
	}
}
