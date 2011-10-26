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


#ifndef SGE_D3D9_OFFSCREEN_TARGET_HPP_INCLUDED
#define SGE_D3D9_OFFSCREEN_TARGET_HPP_INCLUDED

#include <sge/d3d9/offscreen_target_fwd.hpp>
#include <sge/d3d9/basic_target.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_ptr.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/target.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace d3d9
{

class offscreen_target
:
	public d3d9::basic_target<
		sge::renderer::target
	>
{
	FCPPT_NONCOPYABLE(
		offscreen_target
	);

	typedef d3d9::basic_target<
		sge::renderer::target
	> base;
public:
	explicit offscreen_target(
		IDirect3DDevice9 *
	);

	~offscreen_target();
private:
	void
	color_surface(
		renderer::color_surface_ptr,
		renderer::surface_index
	);

	void
	depth_stencil_surface(
		renderer::depth_stencil_surface_ptr
	);

	renderer::optional_dim2 const
	size() const;

	void
	on_activate();

	void
	on_deactivate();

	void
	change_surfaces(
		bool
	);

	typedef fcppt::container::index_map<
		d3d9::surface::color_ptr
	> color_surface_map;

	color_surface_map color_surfaces_;

	d3d9::surface::depth_stencil_ptr depth_stencil_surface_;
};

}
}

#endif
