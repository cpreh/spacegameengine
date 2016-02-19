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


#ifndef SGE_D3D9_TARGET_OFFSCREEN_HPP_INCLUDED
#define SGE_D3D9_TARGET_OFFSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_fwd.hpp>
#include <sge/d3d9/surface/depth_stencil_offscreen_fwd.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/d3d9/target/offscreen_fwd.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace d3d9
{
namespace target
{

class offscreen
:
	public sge::d3d9::target::basic<
		sge::renderer::target::offscreen
	>
{
	FCPPT_NONCOPYABLE(
		offscreen
	);

	typedef sge::d3d9::target::basic<
		sge::renderer::target::offscreen
	> base;
public:
	offscreen(
		IDirect3DDevice9 &,
		sge::renderer::caps::target_surface_indices
	);

	~offscreen()
	override;
private:
	void
	color_surface(
		sge::renderer::color_buffer::optional_surface_ref const &,
		sge::renderer::target::surface_index
	)
	override;

	void
	depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::optional_surface_ref const &
	)
	override;

	bool
	needs_present() const
	override;

	void
	on_activate()
	override;

	void
	on_deactivate()
	override;

	void
	change_surfaces(
		bool
	);

	typedef
	fcppt::optional::reference<
		sge::d3d9::surface::color
	>
	optional_color_surface_ref;

	typedef
	fcppt::optional::reference<
		sge::d3d9::surface::depth_stencil_offscreen
	>
	optional_depth_stencil_surface_ref;

	typedef
	fcppt::container::index_map<
		sge::d3d9::target::offscreen::optional_color_surface_ref
	>
	color_surface_map;

	color_surface_map color_surfaces_;

	sge::d3d9::target::offscreen::optional_depth_stencil_surface_ref depth_stencil_surface_;
};

}
}
}

#endif
