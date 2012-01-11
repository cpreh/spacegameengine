/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/sprite/buffers_option_to_resource_flags.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::resource_flags_field const
sge::sprite::buffers_option_to_resource_flags(
	sge::sprite::buffers_option::type const _options
)
{
	switch(
		_options
	)
	{
	case sge::sprite::buffers_option::static_:
		return
			sge::renderer::resource_flags::none;
	case sge::sprite::buffers_option::dynamic:
		return
			sge::renderer::resource_flags_field(
				sge::renderer::resource_flags::dynamic
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
