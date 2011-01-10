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


#ifndef SGE_GUI_SPRITE_CHOICES_HPP_INCLUDED
#define SGE_GUI_SPRITE_CHOICES_HPP_INCLUDED

#include <sge/gui/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_visibility.hpp>
#include <sge/sprite/choices.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace gui
{
namespace sprite
{

typedef sge::sprite::choices<
	type_choices,
	boost::mpl::vector5<
		sge::sprite::with_dim,
		sge::sprite::with_texture,
		sge::sprite::with_depth,
		sge::sprite::with_visibility,
		sge::sprite::with_color
	>
> choices;

}
}
}

#endif
