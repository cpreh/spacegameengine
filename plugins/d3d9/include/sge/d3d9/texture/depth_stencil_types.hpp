//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/d3d_texture_unique_ptr.hpp>
#include <sge/d3d9/texture/optional_locked_rect.hpp>
#include <sge/renderer/texture/depth_stencil_fwd.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

struct depth_stencil_types
{
	typedef sge::renderer::texture::depth_stencil base;

	typedef sge::renderer::texture::planar_parameters parameters;

	typedef IDirect3DTexture9 d3d_type;

	typedef sge::d3d9::optional_lock_rect lock_dest;

	typedef sge::d3d9::texture::optional_locked_rect locked_dest;

	typedef sge::d3d9::texture::d3d_texture_unique_ptr unique_ptr;

	typedef fcppt::function<
		D3DLOCKED_RECT(
			d3d_type *,
			sge::renderer::texture::stage,
			lock_dest const &,
			sge::d3d9::lock_flags
		)
	> lock_function;

	typedef fcppt::function<
		void (
			d3d_type *,
			sge::renderer::texture::stage
		)
	> unlock_function;

	typedef fcppt::function<
		unique_ptr(
			IDirect3DDevice9 *,
			parameters const &,
			D3DFORMAT,
			D3DPOOL,
			sge::d3d9::usage
		)
	> create_function;

	static create_function const
	create();
};

}
}
}

#endif
