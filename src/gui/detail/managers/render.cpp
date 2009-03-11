#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widget.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/power.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <sge/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("render manager"),
	false);
}

sge::gui::detail::managers::render::dirt::dirt(
	sge::gui::widget &_widget,
	sge::gui::rect const &_rect)
	: widget_(&_widget),
	  rect_(_rect)
{
}

sge::gui::widget &sge::gui::detail::managers::render::dirt::widget()
{
	return *widget_;
}

sge::gui::widget const &sge::gui::detail::managers::render::dirt::widget() const
{
	return *widget_;
}

sge::gui::rect const sge::gui::detail::managers::render::dirt::rect() const
{
	return rect_;
}

sge::gui::detail::managers::render::render(
	renderer::device_ptr const _rend,
	managers::mouse &_mouse)
	: rend(_rend),
	  ss(rend),
		mouse_(_mouse)
{
}

void sge::gui::detail::managers::render::add(widget &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding new widget"));
	if (!w.parent_widget())
		widgets[&w] = widget_data();
}

void sge::gui::detail::managers::render::activation(
	widget &w,
	activation_state::type const t)
{
	if (w.parent_widget())
		return;
	
	SGE_ASSERT(widgets.find(&w) != widgets.end());

	switch (t)
	{
		case activation_state::active:
			widgets[&w].sprite.visible(true);
		break;
		case activation_state::inactive:
			widgets[&w].sprite.visible(false);
		break;
	}
}

void sge::gui::detail::managers::render::draw()
{
	clean();

	sprite::container sprites;
	BOOST_FOREACH(widget_container::value_type const &w,widgets)
		sprites.push_back(w.second.sprite);
	sprites.push_back(mouse_.cursor());
	ss.render(sprites.begin(),sprites.end());
}

void sge::gui::detail::managers::render::remove(widget &w)
{
	for (dirt_container::iterator i = dirt_.begin();
			 i != dirt_.end();
			 )
	{
		if (&(i->widget()) == &w)
		{
			i = dirt_.erase(i);
			continue;
		}
		i++;
	}

	if (w.parent_widget())
		return;
	
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	widgets.erase(wi);
}

void sge::gui::detail::managers::render::resize(widget &w,dim const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	
	// widget is not a top level widget, so we don't care
	if (wi == widgets.end())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widget from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	widget_data &wd = wi->second;
	
	// check if the current texture is large enough to hold the new widget
	dim const new_dim = 
		dim(
			math::next_pow_2(d.w()),
			math::next_pow_2(d.h()));

	if (!wd.texture || structure_cast<dim>(wd.texture->dim()) == new_dim)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("new resolution is ")
			        << new_dim);

		renderer::texture_ptr const software_texture(
			new renderer::texture_software(
				structure_cast<renderer::texture::dim_type>(new_dim),
				renderer::color_format::rgba8));

		renderer::texture_ptr hardware_texture = rend->create_texture(
			structure_cast<renderer::texture::dim_type>(new_dim),
			renderer::color_format::rgba8,
			renderer::filter::linear,
			renderer::resource_flags::dynamic);
		
		// NOTE: the sprite::object has to get a texture convertible to
		// sge::ogl::texture, so we give it hardware_texture below. the sprite_texture
		// serves as a canvas for the widgets and we pass it here
		wd.texture.reset(
			new renderer::texture_rw(
				software_texture,
				hardware_texture));
								
		wd.sprite = sprite::object(
			sprite::point(
				structure_cast<sprite::point>(
					w.screen_pos())),
			texture::const_part_ptr(
				new texture::part_raw(
					hardware_texture)),
			sprite::dim(
				structure_cast<sprite::dim>(
					new_dim)),
			sprite::defaults::color_,
			static_cast<sprite::depth_type>(1));
		
		switch (w.activation())
		{
			case activation_state::active:
				wd.sprite.visible(true);
			break;
			case activation_state::inactive:
				wd.sprite.visible(false);
			break;
		}
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("resolution suffices, doing nothing"));
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding dirty region ") 
		        << rect(point::null(),d));
		
	invalidate(
		w,
		rect(
			point::null(),
			d));
}

void sge::gui::detail::managers::render::reposition(
	widget &w,
	point const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	// widget is not a top level widget
	if (wi == widgets.end())
		return;

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("repositioning sprite to ") << d);
	// just reset sprite position
	wi->second.sprite.pos() = structure_cast<sprite::point>(d);
}

void sge::gui::detail::managers::render::invalidate(
	widget &w,
	rect const &r)
{
	dirt_.push_back(dirt(w,r));
}

sge::sprite::object &sge::gui::detail::managers::render::connected_sprite(
	widget &w)
{
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	return wi->second.sprite;
}

void sge::gui::detail::managers::render::clean()
{
	if (dirt_.empty())
		return;

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("cleaning dirty regions"));

	BOOST_FOREACH(dirt_container::reference d,dirt_)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("cleaning rect: ")
			        << d.rect() 
							<< SGE_TEXT(" from widget: ")
							<< typeid(d.widget()).name());

		widget &p = d.widget().oldest_parent();

		SGE_ASSERT(widgets.find(&p) != widgets.end());

		rect const to_lock = 
			d.widget().parent_widget()
			? d.widget().absolute_area()
			: rect(point::null(),d.widget().size());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("locking area: ")
			        << to_lock);

		renderer::scoped_texture_lock const lock_(
			widgets[&p].texture,
			math::structure_cast<renderer::lock_rect>(
				to_lock),
			renderer::lock_flags::readwrite);

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("sending invalidate for area: ")
			        << d.rect());

		p.process(
			events::invalid_area(
				lock_.value(),
				d.rect()));
	}

	dirt_.clear();
}
