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
#include <sge/gui/sprite/point.hpp>
#include <sge/gui/sprite/dim.hpp>
#include <sge/gui/sprite/depth_type.hpp>
#include <sge/gui/sprite/parameters.hpp>
#include <sge/gui/log.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/next_pow_2.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <fcppt/texture/part_raw.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <sge/type_name.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/foreach.hpp>
#include <utility>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("managers: render")
	)
);

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
			sge::fcppt::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				d)
			,
			sge::image::color::format::rgba8
		)
	);

	sge::renderer::texture_ptr const hardware_texture =
		rend->create_texture(
			sge::fcppt::math::dim::structure_cast<
				sge::renderer::texture::dim_type
			>(
				d
			),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::dynamic);

	tex =
		sge::make_shared_ptr<
			sge::renderer::texture_rw
		>(
			software_texture,
			hardware_texture
		);

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

sge::gui::detail::managers::render::~render()
{}

void sge::gui::detail::managers::render::add(widgets::base &w)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("adding new widget"));
	widgets::base *w_ptr = &w;

	if (!w.has_parent())
	{
		sge::auto_ptr<
			widget_data
		> to_insert(
			sge::make_auto_ptr<
				widget_data
			>()
		);


		widgets.insert(
			w_ptr,
			to_insert
		);
	}
}

void sge::gui::detail::managers::render::activation(
	widgets::base &w,
	activation_state::type const t)
{
	if (w.has_parent())
		return;

	FCPPT_ASSERT(widgets.find(&w) != widgets.end());

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

	BOOST_FOREACH(
		widget_container::value_type const &w,
		widgets
	)
		sprites_.push_back(
			w.second->sprite
		);

	sprites_.push_back(
		cursor_->sprite()
	);

	ss.render(
		sprites_.begin(),
		sprites_.end(),
		sge::sprite::default_sort(),
		sge::sprite::default_equal()
	);
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
	FCPPT_ASSERT(wi != widgets.end());
	widgets.erase(wi);
}

void sge::gui::detail::managers::render::resize(
	widgets::base &w,
	dim const &d)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		log::_
			<< FCPPT_TEXT("widget ") << type_name(typeid(w))
			<< FCPPT_TEXT(" was resized to ") << d);

	dirt_.erase(&w);

	dirty(
		w,
		rect(
			rect::pos_type::null(),
			d
		)
	);

	widget_container::iterator wi = widgets.find(
		&w);

	// widgets::base is not a top level widget, so we don't care anymore
	if (wi == widgets.end())
		return;

	FCPPT_LOG_DEBUG(
		mylogger,
		log::_
			<< FCPPT_TEXT("resizing widget from ") << w.size()
			<< FCPPT_TEXT(" to ") << d);

	widget_data &wd = *wi->second;

	// check if the current texture is large enough to hold the new widget
	dim const new_dim(
		fcppt::math::next_pow_2(d.w()),
		fcppt::math::next_pow_2(d.h()));

	if (wd.texture && fcppt::math::dim::structure_cast<dim>(wd.texture->dim()) == new_dim)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("texture resolution ")
				<< wd.texture->dim()
				<< FCPPT_TEXT(" suffices, doing nothing"));
		return;
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		log::_
			<< FCPPT_TEXT("new resolution is ")
			<< new_dim
	);

	wd.sprite.texture(
		assign_textures(
			new_dim,
			rend,
			wd.texture
		)
	);

	wd.sprite.size(
		sge::gui::sprite::dim(
			fcppt::math::dim::structure_cast<
				sge::gui::sprite::dim
			>(
				new_dim
			)
		)
	);

	reposition(
		w,
		w.screen_pos()
	);

	z(
		w,
		w.z()
	);

	activation(
		w,
		w.activation()
	);
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
	wi->second->sprite.pos(
		fcppt::math::vector::structure_cast<
			sge::gui::sprite::point
		>(d)
	);
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

sge::gui::sprite::object &
sge::gui::detail::managers::render::connected_sprite(
	widgets::base &w
)
{
	widget_container::iterator wi = widgets.find(&w);
	FCPPT_ASSERT(wi != widgets.end());
	return wi->second->sprite;
}

void sge::gui::detail::managers::render::z(
	widgets::base &w,
	depth_type const _z)
{
	if (!w.has_parent())
		return;

	widgets[&w].sprite.z(
		static_cast<
			sge::gui::sprite::depth_type
		>(
			_z
		)
	);
}

void sge::gui::detail::managers::render::clean()
{
	if (dirt_.empty())
		return;

	FCPPT_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("cleaning dirty regions"));

	BOOST_FOREACH(dirt_container::reference d,dirt_)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("cleaning rect: ")
				<< d.second
				<< FCPPT_TEXT(" from widget: ")
				<< type_info(typeid(*d.first)).name());

		widgets::base &p = d.first->oldest_parent();

		// NOTE: we could remove rectangles which are completely inside this one
		// (maybe order by area first)

		FCPPT_ASSERT(widgets.find(&p) != widgets.end());

		if (!widgets[&p].texture)
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				log::_ << FCPPT_TEXT("cannot lock because oldest parent hasn't been inited yet"));
			continue;
		}

		rect const to_lock(
			d.first->absolute_pos()+d.second.pos(),
			d.second.dim());

		FCPPT_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("trying to lock area: ")
				<< to_lock);

		renderer::scoped_texture_lock const lock_(
			widgets[&p].texture,
			fcppt::math::box::structure_cast<renderer::lock_rect>(
				to_lock),
			renderer::lock_mode::readwrite
		);

		utility::wipe_image_view(
			lock_.value());

		FCPPT_LOG_DEBUG(
			mylogger,
			log::_
				<< FCPPT_TEXT("sending dirty for area: ")
				<< d.second);

		p.process_invalid_area(
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
		sge::gui::sprite::parameters()
		// TODO: what to specify here?
		.default_color()
		.elements()
	)
{}
