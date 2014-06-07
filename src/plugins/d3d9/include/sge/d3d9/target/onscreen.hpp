/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_D3D9_TARGET_ONSCREEN_HPP_INCLUDED


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource_manager_fwd.hpp>
#include <sge/d3d9/surface/color_fwd.hpp>
#include <sge/d3d9/surface/depth_stencil_fwd.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/d3d9/target/onscreen_fwd.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace target
{

class onscreen
:
	public sge::d3d9::target::basic<
		sge::renderer::target::onscreen
	>
{
	FCPPT_NONCOPYABLE(
		onscreen
	);

	typedef sge::d3d9::target::basic<
		sge::renderer::target::onscreen
	> base;
public:
	onscreen(
		IDirect3DDevice9 &,
		sge::image::color::format,
		sge::renderer::target::viewport const &,
		sge::d3d9::resource_manager &,
		sge::renderer::caps::target_surface_indices
	);

	~onscreen();

	sge::renderer::color_buffer::surface const &
	surface() const;
private:
	bool
	needs_present() const;

	void
	on_activate();

	void
	on_deactivate();

	typedef std::unique_ptr<
		sge::d3d9::surface::color
	> color_surface_unique_ptr;

	color_surface_unique_ptr const color_surface_;

	typedef std::unique_ptr<
		sge::d3d9::surface::depth_stencil
	> depth_stencil_surface_unique_ptr;

	depth_stencil_surface_unique_ptr const depth_stencil_surface_;
};

}
}
}

#endif
