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


#ifndef SGE_D3D9_TEXTURE_PLANAR_TYPES_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_PLANAR_TYPES_HPP_INCLUDED

#include <sge/d3d9/texture/d3d_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_rect.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

struct planar_types
{
	typedef sge::renderer::texture::planar base;

	typedef sge::renderer::texture::planar_parameters parameters;

	typedef IDirect3DTexture9 d3d_type;

	typedef d3d9::optional_lock_rect lock_dest;

	typedef texture::optional_locked_rect locked_dest;

	typedef texture::d3d_texture_unique_ptr unique_ptr;

	typedef fcppt::function::object<
		D3DLOCKED_RECT(
			d3d_type *,
			sge::renderer::texture::stage,
			lock_dest const &,
			d3d9::lock_flags
		)
	> lock_function;

	typedef fcppt::function::object<
		void (
			d3d_type *,
			sge::renderer::texture::stage
		)
	> unlock_function;

	typedef fcppt::function::object<
		unique_ptr(
			IDirect3DDevice9 *,
			parameters const &,
			D3DFORMAT,
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
