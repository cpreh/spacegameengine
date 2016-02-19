/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect_fwd.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_rect_fwd.hpp>
#include <sge/d3d9/texture/planar_types_fwd.hpp>
#include <sge/renderer/color_buffer/writable_surface_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

struct planar_types
{
	typedef
	sge::renderer::texture::planar
	base;

	typedef
	sge::renderer::color_buffer::writable_surface
	buffer_base;

	typedef
	sge::renderer::texture::planar_parameters
	parameters;

	typedef
	IDirect3DTexture9
	d3d_type;

	typedef
	IDirect3DSurface9
	d3d_buffer;

	typedef
	sge::d3d9::optional_lock_rect
	lock_dest;

	typedef
	sge::d3d9::texture::optional_locked_rect
	locked_dest;

	typedef
	sge::d3d9::texture::d3d_texture_unique_ptr
	unique_ptr;

	static
	unique_ptr
	create(
		IDirect3DDevice9 &,
		parameters const &,
		D3DFORMAT,
		D3DPOOL,
		sge::d3d9::usage
	);

	static
	D3DLOCKED_RECT
	lock(
		d3d_buffer &,
		lock_dest const &,
		sge::d3d9::lock_flags
	);

	static
	void
	unlock(
		d3d_buffer &
	);
};

}
}
}

#endif
