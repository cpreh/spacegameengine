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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/resource_flags_to_pool.hpp>
#include <sge/d3d9/texture/pool.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


D3DPOOL
sge::d3d9::texture::pool(
	renderer::resource_flags_field const &_flags,
	renderer::texture::capabilities_field const &_caps
)
{
	return
		(
			_caps
			& sge::renderer::texture::capabilities::render_target
		)
		?
			D3DPOOL_DEFAULT
		:
			d3d9::convert::resource_flags_to_pool(
				_flags
			);
}
