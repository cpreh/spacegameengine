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


#include <sge/gui/cursor/default.hpp>
#include <sge/gui/sprite/parameters.hpp>
#include <sge/gui/sprite/depth_type.hpp>
#include <sge/gui/sprite/point.hpp>
#include <sge/gui/media_path.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/dim.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/texture/consume_and_set_fragment.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <sge/text.hpp>

sge::gui::cursor::default_::default_(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const _rend)
:
	rend_(
		_rend),
	texture_(
		rend_,
		image::color::format::rgba8,
		renderer::filter::linear),
	sprite_(
		sge::gui::sprite::parameters()
			.texture(
				texture::consume_and_set_fragment(
					texture_,
					il->load(
						media_path()/
						FCPPT_TEXT("gui")/
						FCPPT_TEXT("cursor.png")
					)->view()
				)
			)
			.texture_size()
			.depth(
				static_cast<sge::gui::sprite::depth_type>(-1)
			)
			.default_color()
			.elements()
	),
	click_(16,16)
{
}

void sge::gui::cursor::default_::pos(
	point const &p)
{
	sge::gui::dim const ss(
		sge::fcppt::math::dim::structure_cast<
			sge::gui::dim
		>(
			rend_->screen_size()
		)
	);

	sprite_.pos(
		fcppt::math::vector::structure_cast<
			sge::gui::sprite::point
		>(
			sge::gui::point(
				sge::fcppt::math::clamp(
					p.x(),
					static_cast<sge::gui::unit>(
						-sprite_.w()
					),
					static_cast<sge::gui::unit>(
						ss.w()+sprite_.w()
					)
				),
				sge::fcppt::math::clamp(
					p.y(),
					static_cast<sge::gui::unit>(
						-sprite_.h()
					),
					static_cast<sge::gui::unit>(
						ss.h()+sprite_.h()
					)
				)
			)
		)
	);
}

sge::gui::point const sge::gui::cursor::default_::pos() const
{
	return fcppt::math::vector::structure_cast<sge::gui::point>(
		sprite_.pos());
}

sge::gui::sprite::object const sge::gui::cursor::default_::sprite() const
{
	return sprite_;
}

void sge::gui::cursor::default_::widget_z(depth_type const z)
{
	sprite_.z(
		std::max(
			sprite_.z(),
			static_cast<sge::gui::sprite::depth_type>(z+1)
		)
	);
}

sge::gui::sprite::object &sge::gui::cursor::default_::mutable_sprite()
{
	return sprite_;
}

sge::gui::cursor::default_::~default_()
{
}
