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
#include <sge/gui/media_path.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/dim.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/texture/consume_and_set_fragment.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/clamp.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>

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
		sprite::parameters()
			.texture(
				texture::consume_and_set_fragment(
					texture_,
					il->load(
						media_path()/
						SGE_TEXT("gui")/
						SGE_TEXT("cursor.png")
					)->view()
				)
			)
			.depth(
				static_cast<sprite::depth_type>(-1)
			)
	),
	click_(16,16)
{
}

void sge::gui::cursor::default_::pos(
	point const &p)
{
	sge::gui::dim const ss = 
		sge::math::dim::structure_cast<sge::gui::dim>(
			rend_->screen_size());
	sprite_.pos() = 
		math::vector::structure_cast<sge::sprite::point>(
			sge::gui::point(
				sge::math::clamp(
					p.x(),
					static_cast<sge::gui::unit>(
						-sprite_.w()),
					static_cast<sge::gui::unit>(
						ss.w()+sprite_.w())),
				sge::math::clamp(
					p.y(),
					static_cast<sge::gui::unit>(
						-sprite_.h()),
					static_cast<sge::gui::unit>(
						ss.h()+sprite_.h()))));
}

sge::gui::point const sge::gui::cursor::default_::pos() const
{
	return math::vector::structure_cast<sge::gui::point>(
		sprite_.pos());
}

sge::sprite::object const sge::gui::cursor::default_::sprite() const
{
	return sprite_;
}

void sge::gui::cursor::default_::widget_z(depth_type const z)
{
	sprite_.z() = 
		std::max(
			sprite_.z(),
			static_cast<sprite::depth_type>(z+1));
}

sge::sprite::object &sge::gui::cursor::default_::mutable_sprite()
{
	return sprite_;
}

sge::gui::cursor::default_::~default_() 
{
	sge::cerr << "destroying cursor\n";
}
