/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/needs_reset_fwd.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_create_fwd.hpp>
#include <sge/d3d9/surface/depth_stencil_create_unique_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_fwd.hpp>
#include <sge/image/ds/format_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil
:
	public sge::renderer::depth_stencil_buffer::surface,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
public:
	depth_stencil(
		sge::d3d9::surface::depth_stencil_create_unique_ptr &&,
		sge::d3d9::needs_reset
	);

	~depth_stencil();

	dim const
	size() const;

	sge::image::ds::format
	format() const;

	IDirect3DSurface9 &
	surface() const;

	const_view const
	lock(
		lock_area const &
	) const
	override;

	view const
	lock(
		lock_area const &,
		sge::renderer::lock_mode
	)
	override;

	void
	unlock() const
	override;
private:
	void
	init();

	void
	on_loss();

	void
	on_reset();

	typedef std::unique_ptr<
		sge::d3d9::surface::depth_stencil_create
	> depth_stencil_create_unique_ptr;

	depth_stencil_create_unique_ptr const create_;

	sge::d3d9::surface::d3d_unique_ptr surface_;
};

}
}
}

#endif
