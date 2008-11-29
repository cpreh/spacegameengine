#include <sge/gui/detail/render_manager.hpp>
#include <sge/gui/detail/mouse_manager.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widget.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("render_manager"),true);
}

sge::gui::detail::render_manager::render_manager(
	renderer::device_ptr const rend,
	mouse_manager &mouse)
	: rend(rend),
	  ss(rend),
		mouse(mouse)
{
}

void sge::gui::detail::render_manager::add(widget &w)
{
	if (!w.parent_widget())
		widgets[&w] = widget_data();
}

void sge::gui::detail::render_manager::draw()
{
	if (!dirt.empty())
		redraw_dirt();

	sprite::system::container sprites;
	BOOST_FOREACH(widgets::value_type const &w,widgets)
		sprites.push_back(w.second.sprite);
	sprites.push_back(mouse.cursor());
	ss.render(sprites.begin(),sprites.end());
}

void sge::gui::detail::render_manager::remove(widget &w)
{
	if (w.parent_widget())
		return;
	
	widget_container::iterator wi = std::find(widgets.begin(),widgets.end(),&w);
	SGE_ASSERT(wi != widgets.end());
	widgets.erase(wi);
}

void sge::gui::detail::render_manager::resize(widget &w,dim const &d)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widget from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	// TODO: if the widget is shrunk, you could fill the extra space with
	// transparent pixels so you don't have to create a whole new texture. if it
	// is enlarged, you could create a texture which is too large so subsequent
	// resize operations won't eat much performance
	widget_data &wd = widgets[&w];

	renderer::texture_ptr software_texture(
		new renderer::texture_software(
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
	wd.texture.reset(
		new renderer::texture_rw(
			software_texture,
			hardware_texture));
							
	wd.sprite = sprite::object(
				sprite::point(math::structure_cast<sprite::unit>(w.pos())),
				texture::part_ptr(new texture::part_raw(hardware_texture)),
				sprite::dim(math::structure_cast<sprite::unit>(d)),
				sprite::defaults::color_,
				static_cast<sprite::depth_type>(1));
	
	dirt.push_back(rect(w.pos(),d));
}

void sge::gui::detail::render_manager::reposition(widget &w,point const &d)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("repositioning sprite to ") << d);
	// just reset sprite position
	widgets[&w].sprite.pos() = math::structure_cast<sprite::unit>(d);
}

void sge::gui::detail::render_manager::invalidate(rect const &r)
{
	dirt.push_back(r);
}

void sge::gui::detail::render_manager::redraw_dirt()
{
	// calculate bounding rect of all dirt rects
	rect const bound = math::bounding<unit>(dirt.begin(),dirt.end());
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("bounding rect of all dirty regions is ") << bound);
	dirt.clear();
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("invalidate called for rect ") << bound 
		        << SGE_TEXT(", checking intersections"));

	// if rects intersect, pass event on to top level widgets
	BOOST_FOREACH(widget_container::value_type &p,widgets)
	{
		widget &w = *p.first;
		widget_data &wd = p.second;

		if (!math::intersects(w.absolute_area(),bound))
			continue;

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("got an intersection with area ") 
							<< w.absolute_area());

		// if it intersects, lock the whole intersection
		rect const widget_area  = w.absolute_area();
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

		w.process(
			events::invalid_area(
				canvas(
					lock_.value(),
					w.absolute_area(),
					is)));

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("invalid_area sent, now unlocking"));
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("checking intersections completed"));
}

