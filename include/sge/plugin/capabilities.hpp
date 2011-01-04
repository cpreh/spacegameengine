/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED
#define SGE_PLUGIN_CAPABILITIES_HPP_INCLUDED

namespace sge
{
namespace plugin
{
namespace capabilities
{
enum type
{
	nothing          = 0,
	renderer         = 1,
	input            = 1 << 1,
	image2d_loader   = 1 << 2,
	audio_player     = 1 << 3,
	font             = 1 << 4,
	audio_loader     = 1 << 5,
	collision_system = 1 << 6,
	model_loader     = 1 << 7,
	char_conv        = 1 << 8,
	last_guard_      = 1 << 9
};
}

}
}

#endif
