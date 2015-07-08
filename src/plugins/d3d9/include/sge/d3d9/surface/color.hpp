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


#ifndef SGE_D3D9_SURFACE_COLOR_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/color_create_unique_ptr.hpp>
#include <sge/d3d9/surface/color_fwd.hpp>
#include <sge/d3d9/surface/color_holder_fwd.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class color
:
	public sge::renderer::color_buffer::surface,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		color
	);
public:
	color(
		IDirect3DDevice9 &,
		sge::image::color::format,
		sge::d3d9::surface::color_create_unique_ptr &&
	);

	~color()
	override;

	sge::renderer::color_buffer::surface::view const
	lock(
		sge::renderer::color_buffer::surface::lock_area const &,
		sge::renderer::lock_mode
	)
	override;

	sge::renderer::color_buffer::surface::const_view const
	lock(
		sge::renderer::color_buffer::surface::lock_area const &
	) const
	override;

	void
	unlock() const
	override;

	dim const
	size() const
	override;

	color_format
	format() const
	override;

	IDirect3DSurface9 &
	surface() const;
private:
	IDirect3DSurface9 &
	lock_surface() const;

	void
	init();

	void
	on_loss()
	override;

	void
	on_reset()
	override;

	IDirect3DDevice9 &device_;

	sge::d3d9::surface::color_create_unique_ptr const create_;

	sge::image::color::format const format_;

	typedef
	fcppt::unique_ptr<
		sge::d3d9::surface::color_holder
	>
	color_holder_unique_ptr;

	typedef
	fcppt::optional<
		color_holder_unique_ptr
	>
	optional_color_holder_unique_ptr;

	optional_color_holder_unique_ptr color_holder_;

	mutable sge::d3d9::surface::optional_d3d_unique_ptr temp_surface_;
};

}
}
}

#endif
