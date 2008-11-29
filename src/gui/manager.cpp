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

#include <sge/image/object.hpp>
#include <sge/image/loader.hpp>
#include <sge/renderer/device.hpp>
#include <sge/input/classification.hpp>
#include <sge/media.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/input/system.hpp>
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
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("manager"),true);
}


sge::gui::manager::manager(
	renderer::device_ptr const rend,
	image::loader_ptr const il,
	input::system_ptr const is,
	font::system_ptr const fs,
	skin_ptr skin_)
	: rend(rend),
	  il(il),
	  is(is),
		fs(fs),
		standard_font_(
			fs->create_font(sge::media_path()/SGE_TEXT("fonts/default.ttf"),15)),
		ss(rend),
		skin_(skin_),
		mouse_(is,il,rend,*skin_),
		keyboard_(is)
{
}

void sge::gui::manager::invalidate(rect const &r)
{
	dirt_.push_back(r);
}

void sge::gui::manager::invalidate(widget &w)
{
	recompiles_.insert(&w);
}

void sge::gui::manager::draw()
{
	if (!recompiles_.empty())
		recompile();
	
	if (!dirt_.empty())
		redraw_dirt();

	sprite::system::container sprites;
	BOOST_FOREACH(widget_data &w,widgets_)
		sprites.push_back(w.spr);
	sprites.push_back(mouse_.cursor());
	ss.render(sprites.begin(),sprites.end());
}

sge::font::metrics_ptr const sge::gui::manager::standard_font()
{
	return standard_font_;
}

sge::gui::skin_ptr const sge::gui::manager::skin() 
{ 
	return skin_; 
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

void sge::gui::manager::add(widget &w)
{
	keyboard_.widget_add(w);
	mouse_.widget_add(w);
	recompiles_.insert(&w);

	if (!w.parent_widget())
		widgets_.push_back(widget_data(w,renderer::texture_ptr(),sprite::object()));
}

void sge::gui::manager::remove(widget &w)
{
	keyboard_.widget_remove(w);
	mouse_.widget_remove(w);
	recompiles_.insert(&w);

	if (!w.parent_widget())
		widgets_.erase(std::find_if(widgets_.begin(),widgets_.end(),
			boost::lambda::bind(&widget_data::ptr,boost::lambda::_1) == 
				boost::lambda::constant(&w)));
}

void sge::gui::manager::resize(widget &w,dim const &d)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widget from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	// TODO: if the widget is shrunk, you could fill the extra space with
	// transparent pixels so you don't have to create a whole new texture. if it
	// is enlarged, you could create a texture which is too large so subsequent
	// resize operations won't eat much performance
	widget_data &wd = data(w);

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

void sge::gui::manager::reposition(widget &w,point const &d)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("repositioning sprite to ") << d);
	// just reset sprite position
	data(w).spr.pos() = math::structure_cast<sprite::unit>(d);
}

sge::gui::manager::widget_data &sge::gui::manager::data(widget &w)
{
	widget_container::iterator wi = data_iterator(w);
	SGE_ASSERT_MESSAGE(wi != widgets_.end(),SGE_TEXT("widget is not a top level widget"));
	return *wi;
}

sge::gui::manager::widget_container::iterator sge::gui::manager::data_iterator(
	widget &w)
{
	return std::find_if(widgets_.begin(),widgets_.end(),
			boost::lambda::bind(&widget_data::ptr,boost::lambda::_1) == 
				boost::lambda::constant(&w));
}

sge::gui::manager::widget_data &sge::gui::manager::parent_widget_data(widget &w)
{
	// top level widget? then forward to data
	if (!w.parent_widget())
		return data(w);
	return parent_widget_data(*w.parent_widget());
}

sge::gui::detail::keyboard_manager &sge::gui::manager::keyboard()
{
	return keyboard_;
}

void sge::gui::manager::redraw_dirt()
{
	// calculate bounding rect of all dirt rects
	rect const bound = sge::math::bounding<unit>(dirt_.begin(),dirt_.end());
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("bounding rect of all dirty regions is ") << bound);
	dirt_.clear();
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("invalidate called for rect ") << bound 
		        << SGE_TEXT(", checking intersections"));

	// if rects intersect, pass event on to top level widgets
	BOOST_FOREACH(widget_data &wd,widgets_)
	{
		if (math::intersects(wd.ptr->absolute_area(),bound))
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("got an intersection with area ") 
				        << wd.ptr->absolute_area());

			// if it intersects, lock the whole intersection
			rect const widget_area  = wd.ptr->absolute_area();
			rect const is = math::intersection(widget_area,bound);

			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("intersection is ") << is);

			// we have to convert the global intersection rect to a local one so we
			// can lock the texture
			rect const is_local(
				is.left()-widget_area.left(),
				is.top()-widget_area.top(),
				is.right()-widget_area.left(),
				is.bottom()-widget_area.top());

			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("locking ") << is_local 
				        << SGE_TEXT(" and sending invalid_area event"));

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

			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("invalid_area sent, now unlocking"));
		}
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("checking intersections completed"));
}

void sge::gui::manager::recompile()
{
	// The standard behaviour for widgets which need recompiling is to determine
	// their topmost parent. Then, each parent is recompile completely
	recompile_container parents;
	BOOST_FOREACH(widget *w,recompiles_)
	{
		widget *parent = 0,*it = w;
		while (it != 0)
		{
			parent = it;
			it = it->parent_widget();
		}

		SGE_ASSERT(parent != 0);

		parents.insert(parent);
	}

	BOOST_FOREACH(widget *w,parents)
	{
		w->compile();
		resize(*w,w->size());
		reposition(*w,w->pos());
	}

	mouse_.recalculate_focus();
	recompiles_.clear();
}
