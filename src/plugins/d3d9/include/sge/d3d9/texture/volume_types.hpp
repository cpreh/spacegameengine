/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_box_fwd.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_volume_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_box_fwd.hpp>
#include <sge/d3d9/texture/volume_types_fwd.hpp>
#include <sge/renderer/color_buffer/volume.hpp>
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

struct volume_types
{
	typedef sge::renderer::texture::volume base;

	typedef sge::renderer::color_buffer::volume buffer_base;

	typedef sge::renderer::texture::volume_parameters parameters;

	typedef IDirect3DVolumeTexture9 d3d_type;

	typedef IDirect3DVolume9 d3d_buffer;

	typedef sge::d3d9::optional_lock_box lock_dest;

	typedef sge::d3d9::texture::optional_locked_box locked_dest;

	typedef sge::d3d9::texture::d3d_volume_texture_unique_ptr unique_ptr;

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
	D3DLOCKED_BOX const
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
