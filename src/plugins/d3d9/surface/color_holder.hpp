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


#ifndef SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED

#include "color_holder_fwd.hpp"
#include "d3d_unique_ptr.hpp"
#include "d3d_scoped_ptr.hpp"
#include "../d3dinclude.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

class color_holder
{
	FCPPT_NONCOPYABLE(
		color_holder
	);
public:
	explicit color_holder(
		surface::d3d_unique_ptr
	);

	~color_holder();

	IDirect3DSurface9 *
	get() const;

	sge::renderer::dim2 const &
	size() const;

	sge::image::color::format::type
	format() const;

	bool
	is_render_target() const;
private:
	surface::d3d_scoped_ptr const surface_;

	sge::renderer::dim2 const size_;

	sge::image::color::format::type const format_;

	bool const is_render_target_;
};

}
}
}

#endif
