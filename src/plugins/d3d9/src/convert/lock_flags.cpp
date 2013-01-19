/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::d3d9::lock_flags const
sge::d3d9::convert::lock_flags(
	sge::renderer::lock_flags::method const _method,
	sge::renderer::resource_flags_field const &_flags
)
{
	switch(
		_method
	)
	{
	case sge::renderer::lock_flags::method::read:
		return
			fcppt::strong_typedef_construct_cast<
				sge::d3d9::lock_flags
			>(
				D3DLOCK_READONLY
			);
	case sge::renderer::lock_flags::method::write:
		if(
			_flags & sge::renderer::resource_flags::dynamic
		)
			return
				fcppt::strong_typedef_construct_cast<
					sge::d3d9::lock_flags
				>(
					D3DLOCK_DISCARD
				);
		// fall through
	case sge::renderer::lock_flags::method::readwrite:
		return
			sge::d3d9::lock_flags(
				0u
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
