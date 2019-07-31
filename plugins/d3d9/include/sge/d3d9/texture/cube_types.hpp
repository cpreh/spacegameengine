//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_CUBE_TYPES_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_CUBE_TYPES_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect_fwd.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/cube_types_fwd.hpp>
#include <sge/d3d9/texture/d3d_cube_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_rect_fwd.hpp>
#include <sge/renderer/color_buffer/writable_surface_fwd.hpp>
#include <sge/renderer/texture/cube_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

struct cube_types
{
	typedef
	sge::renderer::texture::cube
	base;

	typedef
	sge::renderer::color_buffer::writable_surface
	buffer_base;

	typedef
	sge::renderer::texture::cube_parameters
	parameters;

	typedef
	IDirect3DCubeTexture9
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
	sge::d3d9::texture::d3d_cube_texture_unique_ptr
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
