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


#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_NATIVE_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_NATIVE_HPP_INCLUDED

#include "d3d_unique_ptr.hpp"
#include "depth_stencil_create.hpp"
#include "../d3dinclude.hpp"
#include "../multi_sample_quality.hpp"
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil_native
:
	public surface::depth_stencil_create
{
	FCPPT_NONCOPYABLE(
		depth_stencil_native
	);
public:
	depth_stencil_native(
		IDirect3DDevice9 *,
		sge::renderer::dim2 const &,
		sge::renderer::depth_stencil_format::type,
		D3DMULTISAMPLE_TYPE,
		d3d9::multi_sample_quality
	);

	~depth_stencil_native();

	surface::d3d_unique_ptr
	create() const;
private:
	IDirect3DDevice9 *const device_;

	sge::renderer::dim2 const dim_;

	sge::renderer::depth_stencil_format::type const format_;

	D3DMULTISAMPLE_TYPE const samples_;

	d3d9::multi_sample_quality const multi_sample_quality_;
};

}
}
}

#endif
