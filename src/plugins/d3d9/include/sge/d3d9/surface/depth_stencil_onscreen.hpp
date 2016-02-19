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


#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_ONSCREEN_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_ONSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil_onscreen
:
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		depth_stencil_onscreen
	);
public:
	explicit
	depth_stencil_onscreen(
		IDirect3DDevice9 &
	);

	~depth_stencil_onscreen()
	override;

	sge::d3d9::surface::optional_d3d_ref
	surface() const;
private:
	void
	init();

	void
	on_loss()
	override;

	void
	on_reset()
	override;

	IDirect3DDevice9 &device_;

	sge::d3d9::surface::optional_d3d_unique_ptr surface_;
};

}
}
}

#endif
