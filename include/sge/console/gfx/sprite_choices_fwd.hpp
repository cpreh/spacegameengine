/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_GFX_SPRITE_CHOICES_FWD_HPP_INCLUDED
#define SGE_CONSOLE_GFX_SPRITE_CHOICES_FWD_HPP_INCLUDED

#include <sge/console/gfx/sprite_elements_fwd.hpp>
#include <sge/console/gfx/sprite_type_choices_fwd.hpp>
#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/pos_fwd.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>


namespace sge
{
namespace console
{
namespace gfx
{

typedef
sge::sprite::config::choices<
	sge::console::gfx::sprite_type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos_or_center
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::maybe
	>,
	sge::console::gfx::sprite_elements
>
sprite_choices;

}
}
}

#endif
