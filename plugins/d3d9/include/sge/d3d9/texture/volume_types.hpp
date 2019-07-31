//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_VOLUME_TYPES_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_TYPES_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_box_fwd.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_volume_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_box_fwd.hpp>
#include <sge/d3d9/texture/volume_types_fwd.hpp>
#include <sge/renderer/color_buffer/writable_volume_fwd.hpp>
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
	typedef
	sge::renderer::texture::volume
	base;

	typedef
	sge::renderer::color_buffer::writable_volume
	buffer_base;

	typedef
	sge::renderer::texture::volume_parameters
	parameters;

	typedef
	IDirect3DVolumeTexture9
	d3d_type;

	typedef
	IDirect3DVolume9
	d3d_buffer;

	typedef
	sge::d3d9::optional_lock_box
	lock_dest;

	typedef
	sge::d3d9::texture::optional_locked_box
	locked_dest;

	typedef
	sge::d3d9::texture::d3d_volume_texture_unique_ptr
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
	D3DLOCKED_BOX
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
