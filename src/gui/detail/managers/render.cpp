#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/power.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <sge/cerr.hpp>
#include <sge/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("managers: render"),
	false);

void wipe_image_view(
	sge::renderer::image_view const &v)
{
	sge::renderer::fill_pixels(
		v,
		sge::renderer::colors::transparent());
}

void wipe_texture(
	sge::renderer::texture_ptr const t)
{
	sge::renderer::scoped_texture_lock const lock_(
		t,
		sge::renderer::lock_rect(
			t->dim()),
		sge::renderer::lock_flags::readwrite);
	
	wipe_image_view(
		lock_.value());
}
}

sge::gui::detail::managers::render::render(
	renderer::device_ptr const _rend,
	cursor &_cursor)
	: rend(_rend),
	  ss(rend),
		cursor_(_cursor)
{
}

void sge::gui::detail::managers::render::add(widgets::base &w)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding new widget"));
	widgets::base *w_ptr = &w;
	if (!w.has_parent())
		widgets.insert(
			w_ptr,
			new widget_data());
}

void sge::gui::detail::managers::render::activation(
	widgets::base &w,
	activation_state::type const t)
{
	if (w.has_parent())
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

void sge::gui::detail::managers::render::update()
{
	clean();
}

void sge::gui::detail::managers::render::draw()
{
	sprites_.clear();
	BOOST_FOREACH(widget_container::value_type const &w,widgets)
		sprites_.push_back(w.second->sprite);
	sprites_.push_back(
		cursor_.sprite());
	ss.render(
		sprites_.begin(),
		sprites_.end());
}

void sge::gui::detail::managers::render::remove(
	widgets::base &w)
{
	dirt_.erase(&w);

	// the compiler manager takes care of redrawing the parent widget, so we can
	// exit here
	if (w.has_parent())
		return;
	
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	widgets.erase(wi);
}

void sge::gui::detail::managers::render::resize(
	widgets::base &w,
	dim const &d)
{
	dirt_.erase(&w);

	dirty(
		w,
		rect(
			d));

	widget_container::iterator wi = widgets.find(
		&w);
	
	// widgets::base is not a top level widget, so we don't care anymore
	if (wi == widgets.end())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widgets::base from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	widget_data &wd = *wi->second;
	
	// check if the current texture is large enough to hold the new widget
	dim const new_dim = 
		dim(
			math::next_pow_2(d.w()),
			math::next_pow_2(d.h()));

	if (!wd.texture || structure_cast<dim>(wd.texture->dim()) != new_dim)
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

		wipe_texture(wd.texture);
								
		wd.sprite.pos() = sprite::point(
				structure_cast<sprite::point>(
					w.screen_pos()));

		wd.sprite.texture(
			texture::const_part_ptr(
				new texture::part_raw(
					hardware_texture)));

		wd.sprite.size() = sprite::dim(
				structure_cast<sprite::dim>(
					new_dim));

		wd.sprite.z() = static_cast<sprite::depth_type>(1);
		
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
			log::_1 << SGE_TEXT("texture resolution ")
			        << wd.texture->dim() 
							<< SGE_TEXT(" suffices, doing nothing"));
	}
}

void sge::gui::detail::managers::render::reposition(
	widgets::base &w,
	point const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	// widgets::base is not a top level widget
	if (wi == widgets.end())
		return;

	/*
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("repositioning sprite to ") << d);
		*/
	// just reset sprite position
	wi->second->sprite.pos() = structure_cast<sprite::point>(d);
}

void sge::gui::detail::managers::render::dirty(
	widgets::base &w,
	rect const &r)
{
	dirt_.insert(std::make_pair(&w,r));
}

sge::sprite::object &sge::gui::detail::managers::render::connected_sprite(
	widgets::base &w)
{
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	return wi->second->sprite;
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
			        << d.second 
							<< SGE_TEXT(" from widget: ")
							<< typeid(*d.first).name());

		widgets::base &p = d.first->oldest_parent();

		// FIXME: we could remove rectangles which are completely inside this one
		// (maybe order by area first)

		SGE_ASSERT(widgets.find(&p) != widgets.end());

		rect const to_lock(
			d.first->absolute_pos()+d.second.pos(),
			d.second.dim());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("locking area: ")
			        << to_lock);

		renderer::scoped_texture_lock const lock_(
			widgets[&p].texture,
			math::structure_cast<renderer::lock_rect>(
				to_lock),
			renderer::lock_flags::readwrite);

		wipe_image_view(lock_.value());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("sending dirty for area: ")
			        << d.second);

		p.process(
			events::invalid_area(
				lock_.value(),
				to_lock));
	}

	dirt_.clear();
}
