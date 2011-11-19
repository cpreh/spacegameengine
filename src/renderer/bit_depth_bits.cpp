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


#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/bit_depth_bits.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::size_type
sge::renderer::bit_depth_bits(
	renderer::bit_depth::type const _bit_depth
)
{
	switch(
		_bit_depth
	)
	{
	case renderer::bit_depth::depth16:
		return 16;
	case renderer::bit_depth::depth32:
		return 32;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
