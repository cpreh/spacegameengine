//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_volume_texture.hpp>
#include <sge/d3d9/texture/volume_types.hpp>
#include <sge/d3d9/volumefuncs/lock_box.hpp>
#include <sge/d3d9/volumefuncs/unlock_box.hpp>


sge::d3d9::texture::volume_types::unique_ptr
sge::d3d9::texture::volume_types::create(
	IDirect3DDevice9 &_device,
	parameters const &_parameters,
	D3DFORMAT const _format,
	D3DPOOL const _pool,
	sge::d3d9::usage const _usage
)
{
	return
		sge::d3d9::devicefuncs::create_volume_texture(
			_device,
			_parameters,
			_format,
			_pool,
			_usage
		);
}

D3DLOCKED_BOX
sge::d3d9::texture::volume_types::lock(
	d3d_buffer &_buffer,
	lock_dest const &_lock_dest,
	sge::d3d9::lock_flags const _flags
)
{
	return
		sge::d3d9::volumefuncs::lock_box(
			_buffer,
			_lock_dest,
			_flags
		);
}

void
sge::d3d9::texture::volume_types::unlock(
	d3d_buffer &_buffer
)
{
	sge::d3d9::volumefuncs::unlock_box(
		_buffer
	);
}
