/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "../../utility/wipe_texture.hpp"
#include "../../utility/wipe_image_view.hpp"
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/cursor/base.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/math/next_pow_2.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <sge/type_name.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <utility>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("managers: render"),
	false);

// NOTE: the sprite::object has to get a texture convertible to
// sge::ogl::texture, so we give it hardware_texture below. the sprite_texture
// serves as a canvas for the widgets and we pass it here
sge::texture::const_part_ptr assign_textures(
	sge::gui::dim const &d,
	sge::renderer::device_ptr const rend,
	sge::renderer::texture_ptr &tex)
{
	sge::renderer::texture_ptr const software_texture(
		sge::make_shared_ptr<
			sge::renderer::texture_software
		>(
			sge::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				d)
			,
			sge::image::color::format::rgba8
		)
	);

	sge::renderer::texture_ptr const hardware_texture = 
		rend->create_texture(
			sge::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				d
			),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::dynamic);
	
	tex.reset(
		new sge::renderer::texture_rw(
			software_texture,
			hardware_texture));

	sge::gui::utility::wipe_texture(
		tex);

	return 
		sge::texture::const_part_ptr(
			sge::make_shared_ptr<
				sge::texture::part_raw
			>(
				hardware_texture));
}

}

sge::gui::detail::managers::render::render(
	renderer::device_ptr const _rend,
	cursor::base_ptr _cursor)
:
	rend(_rend),
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
		cursor_->sprite());
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
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("widget ") << type_name(typeid(w))
		        << SGE_TEXT(" was resized to ") << d);

	dirt_.erase(&w);

	dirty(
		w,
		rect(
			rect::point_type::null(),
			d
		)
	);

	widget_container::iterator wi = widgets.find(
		&w);
	
	// widgets::base is not a top level widget, so we don't care anymore
	if (wi == widgets.end())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widget from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	widget_data &wd = *wi->second;
	
	// check if the current texture is large enough to hold the new widget
	dim const new_dim(
		math::next_pow_2(d.w()),
		math::next_pow_2(d.h()));

	if (wd.texture && math::dim::structure_cast<dim>(wd.texture->dim()) == new_dim)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("texture resolution ")
			        << wd.texture->dim() 
							<< SGE_TEXT(" suffices, doing nothing"));
		return;
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("new resolution is ")
						<< new_dim);

	wd.sprite.texture(
		assign_textures(
			new_dim,
			rend,
			wd.texture));
							
	wd.sprite.size() = 
		sprite::dim(
			math::dim::structure_cast<
				sprite::dim
			>(
				new_dim
			)
		);

	reposition(
		w,
		w.screen_pos());

	z(
		w,
		w.z());

	activation(
		w,
		w.activation());
}

void sge::gui::detail::managers::render::reposition(
	widgets::base &w,
	point const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	// widgets::base is not a top level widget
	if (wi == widgets.end())
		return;

	// just reset sprite position
	wi->second->sprite.pos() = math::vector::structure_cast<sprite::point>(d);
}

void sge::gui::detail::managers::render::dirty(
	widgets::base &w,
	rect const &r)
{
	dirt_.insert(
		std::make_pair(
			&w,
			r));
}

sge::sprite::object &sge::gui::detail::managers::render::connected_sprite(
	widgets::base &w)
{
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	return wi->second->sprite;
}

void sge::gui::detail::managers::render::z(
	widgets::base &w,
	depth_type const _z)
{
	if (!w.has_parent())
		return;
	
	widgets[&w].sprite.z() = 
		static_cast<sprite::depth_type>(
			_z);
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
			log::_1
				<< SGE_TEXT("cleaning rect: ")
				<< d.second 
				<< SGE_TEXT(" from widget: ")
				<< type_info(typeid(*d.first)).name());

		widgets::base &p = d.first->oldest_parent();

		// NOTE: we could remove rectangles which are completely inside this one
		// (maybe order by area first)

		SGE_ASSERT(widgets.find(&p) != widgets.end());

		if (!widgets[&p].texture)
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("cannot lock because oldest parent hasn't been inited yet"));
			continue;
		}

		rect const to_lock(
			d.first->absolute_pos()+d.second.pos(),
			d.second.dim());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("trying to lock area: ")
			        << to_lock);

		renderer::scoped_texture_lock const lock_(
			widgets[&p].texture,
			math::rect::structure_cast<renderer::lock_rect>(
				to_lock),
			renderer::lock_flags::readwrite);

		utility::wipe_image_view(
			lock_.value());

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

sge::gui::detail::managers::render::widget_data::widget_data()
:
	texture(),
	sprite(
		sge::sprite::parameters()
	)
{}
