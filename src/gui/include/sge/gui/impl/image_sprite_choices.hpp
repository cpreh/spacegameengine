/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_GUI_IMPL_IMAGE_SPRITE_CHOICES_HPP_INCLUDED
#define SGE_GUI_IMPL_IMAGE_SPRITE_CHOICES_HPP_INCLUDED

#include <sge/gui/impl/sprite_type_choices.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace gui
{
namespace impl
{

template<
	sge::sprite::config::texture_coordinates TextureCoordinates,
	sge::sprite::config::texture_size_option TextureSize
>
using
image_sprite_choices
=
sge::sprite::config::choices<
	sge::gui::impl::sprite_type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		TextureSize
	>,
	boost::mpl::vector1<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			TextureCoordinates,
			sge::sprite::config::texture_ownership::reference
		>
	>
>;

}
}
}

#endif
