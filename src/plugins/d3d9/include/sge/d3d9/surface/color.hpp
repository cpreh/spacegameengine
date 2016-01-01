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
#include <sge/d3d9/surface/color_create_function.hpp>
#include <sge/d3d9/surface/color_fwd.hpp>
#include <sge/d3d9/surface/color_holder_fwd.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class color
:
	public sge::renderer::color_buffer::readable_surface,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		color
	);
public:
	color(
		IDirect3DDevice9 &,
		sge::image::color::format,
		sge::d3d9::surface::color_create_function const &
	);

	~color()
	override;

	sge::image2d::view::const_object
	lock_c(
		sge::renderer::lock_rect const &
	) const
	override;

	void
	unlock() const
	override;

	sge::renderer::dim2
	size() const
	override;

	sge::image::color::format
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

	sge::d3d9::surface::color_create_function const create_;

	sge::image::color::format const format_;

	typedef
	fcppt::unique_ptr<
		sge::d3d9::surface::color_holder
	>
	color_holder_unique_ptr;

	typedef
	fcppt::optional::object<
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
