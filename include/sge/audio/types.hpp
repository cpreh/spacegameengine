/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#ifndef SGE_AUDIO_TYPES_HPP_INCLUDED
#define SGE_AUDIO_TYPES_HPP_INCLUDED

#include "../raw_vector.hpp"
#include "../su.hpp"
#include "../math/vector.hpp"
#include "../export.hpp"
#include <cstddef>

namespace sge
{
namespace audio
{
typedef unsigned channel_type;
typedef std::size_t sample_count;
typedef raw_vector<unsigned char> sample_container;

typedef space_unit unit;
typedef math::vector3 point;

struct angle
{
	point forward,up;

	SGE_SYMBOL angle();
	SGE_SYMBOL angle(point const &forward,point const &up);
};
}
}

#endif
