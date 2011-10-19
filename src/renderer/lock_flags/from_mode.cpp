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


#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::renderer::lock_flags::method::type
sge::renderer::lock_flags::from_mode(
	renderer::lock_mode::type const _mode
)
{
	switch(
		_mode
	)
	{
	case renderer::lock_mode::writeonly:
		return lock_flags::method::write;
	case renderer::lock_mode::readwrite:
		return lock_flags::method::readwrite;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
