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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_LOCKED_PART_INTERVAL_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_LOCKED_PART_INTERVAL_HPP_INCLUDED

#include "lock_interval.hpp"
#include <sge/renderer/vf/dynamic/locked_part_fwd.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

detail::lock_interval const
locked_part_interval(
	dynamic::locked_part const &
);

}
}
}
}
}

#endif
