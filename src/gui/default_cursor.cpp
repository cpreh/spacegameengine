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
#include <sge/gui/default_cursor.hpp>
#include <sge/gui/media_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/texture/consume_and_set_fragment.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>

sge::gui::default_cursor::default_cursor(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
:
	texture_(
		rend,
		renderer::color_format::rgba8,
		renderer::filter::linear),
	sprite_(
		sprite::parameters()
			.texture(
				texture::consume_and_set_fragment(
					texture_,
					il->load(
							media_path()/
							SGE_TEXT("gui")/
							SGE_TEXT("cursor.png"))
						->view()))
			.depth(
				static_cast<sprite::depth_type>(-1))),
	click_(16,16)
{
}

void sge::gui::default_cursor::pos(
	point const &p)
{
	sprite_.pos() = sge::structure_cast<sge::sprite::point>(
		p);
}

sge::gui::point const sge::gui::default_cursor::pos() const
{
	return sge::structure_cast<sge::gui::point>(
		sprite_.pos());
}

sge::sprite::object const sge::gui::default_cursor::sprite() const
{
	return sprite_;
}

void sge::gui::default_cursor::widget_z(depth_type const z)
{
	sprite_.z() = 
		std::max(
			sprite_.z(),
			static_cast<sprite::depth_type>(z+1));
}

sge::sprite::object &sge::gui::default_cursor::mutable_sprite()
{
	return sprite_;
}

sge::gui::default_cursor::~default_cursor() {}
