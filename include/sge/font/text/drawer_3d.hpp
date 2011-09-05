/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_TEXT_DRAWER_3D_HPP_INCLUDED
#define SGE_FONT_TEXT_DRAWER_3D_HPP_INCLUDED

#include <sge/font/text/drawer.hpp>
#include <sge/font/text/symbol.hpp>
#include <sge/font/text/char_type.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/image_view.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <map>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace font
{
namespace text
{

class SGE_CLASS_SYMBOL drawer_3d
:
	public text::drawer
{
	FCPPT_NONCOPYABLE(
		drawer_3d
	);
public:
	SGE_FONT_TEXT_SYMBOL
	drawer_3d(
		renderer::device &,
		image::color::any::object const &
	);

	SGE_FONT_TEXT_SYMBOL
	~drawer_3d();

	SGE_FONT_TEXT_SYMBOL
	void
	begin_rendering(
		drawer::size_type buffer_chars,
		font::pos const &start,
		font::dim const &size
	);

	SGE_FONT_TEXT_SYMBOL
	void
	draw_char(
		font::text::char_type,
		font::pos const &,
		font::const_image_view const &
	);

	SGE_FONT_TEXT_SYMBOL
	void
	end_rendering();

	SGE_FONT_TEXT_SYMBOL
	void
	color(
		image::color::any::object const &
	);
private:
	texture::const_part_ptr const
	cached_texture(
		font::text::char_type,
		font::const_image_view const &
	);

	image::color::any::object col_;

	texture::manager texman_;

	typedef std::map<
		font::text::char_type,
		texture::const_part_ptr
	> texture_map;

	texture_map textures_;

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			image::color::rgba8_format
		>,
		boost::mpl::vector3<
			sge::sprite::with_color,
			sge::sprite::with_dim,
			sge::sprite::with_texture
		>
	> sprite_choices;

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef std::vector<
		sprite_object
	> sprite_container;

	sprite_system sys_;

	sprite_container sprites_;
};

}
}
}

#endif
