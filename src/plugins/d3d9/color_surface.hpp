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


#ifndef SGE_D3D9_COLOR_SURFACE_HPP_INCLUDED
#define SGE_D3D9_COLOR_SURFACE_HPP_INCLUDED

#include "color_surface_fwd.hpp"
#include "d3dinclude.hpp"
#include "d3d_surface_scoped_ptr.hpp"
#include "d3d_surface_unique_ptr.hpp"
#include <sge/renderer/color_surface.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{

class color_surface
:
	public sge::renderer::color_surface
{
	FCPPT_NONCOPYABLE(
		color_surface
	);
public:
	explicit color_surface(
		d3d9::d3d_surface_unique_ptr
	);

	~color_surface();

	const_view const
	lock(
		rect const &
	) const;

	void
	unlock() const;

	dim const
	size() const;

	IDirect3DSurface9 *
	surface() const;
private:
	d3d9::d3d_surface_scoped_ptr const surface_;
};

}
}

#endif
