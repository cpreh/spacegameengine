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


#ifndef SGE_D3D9_TEXTURE_VOLUME_TYPES_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_TYPES_HPP_INCLUDED

#include "d3d_volume_texture_unique_ptr.hpp"
#include "optional_lock_box.hpp"
#include "optional_locked_box.hpp"
#include "../d3dinclude.hpp"
#include "../lock_flags.hpp"
#include "../usage.hpp"
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/stage_type.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

struct volume_types
{
	typedef sge::renderer::texture::volume base;

	typedef sge::renderer::texture::volume_parameters parameters;

	typedef IDirect3DVolumeTexture9 d3d_type;

	typedef texture::optional_lock_box lock_dest;

	typedef texture::optional_locked_box locked_dest;

	typedef texture::d3d_volume_texture_unique_ptr unique_ptr;

	typedef fcppt::function::object<
		D3DLOCKED_BOX(
			d3d_type *,
			sge::renderer::stage_type,
			lock_dest const &,
			d3d9::lock_flags
		)
	> lock_function;

	typedef fcppt::function::object<
		void (
			d3d_type *,
			sge::renderer::stage_type
		)
	> unlock_function;

	typedef fcppt::function::object<
		unique_ptr(
			IDirect3DDevice9 *,
			parameters const &,
			D3DPOOL,
			d3d9::usage
		)
	> create_function;

	static create_function const
	create();
};

}
}
}

#endif
