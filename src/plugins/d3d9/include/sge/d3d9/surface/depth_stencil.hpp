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


#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/d3d_scoped_ptr.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_create_fwd.hpp>
#include <sge/d3d9/surface/depth_stencil_create_unique_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_fwd.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil
:
	public sge::renderer::depth_stencil_surface,
	public d3d9::resource
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
public:
	depth_stencil(
		surface::depth_stencil_create_unique_ptr,
		d3d9::needs_reset::type
	);

	~depth_stencil();

	dim const
	size() const;

	renderer::depth_stencil_format::type
	format() const;

	IDirect3DSurface9 *
	surface() const;
private:
	void
	init();

	void
	on_loss();

	void
	on_reset();

	typedef fcppt::scoped_ptr<
		d3d9::surface::depth_stencil_create
	> depth_stencil_create_scoped_ptr;

	depth_stencil_create_scoped_ptr const create_;

	surface::d3d_scoped_ptr surface_;
};

}
}
}

#endif
