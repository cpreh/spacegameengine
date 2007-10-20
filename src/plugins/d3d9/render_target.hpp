/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D_RENDER_TARGET_HPP_INCLUDED
#define SGE_D3D_RENDER_TARGET_HPP_INCLUDED

#include "../../renderer/render_target.hpp"
#include "resource.hpp"
#include "d3dinclude.hpp"

namespace sge
{
namespace d3d9
{

class renderer;

class render_target : public sge::render_target, public resource {
	friend class renderer;
public:
	render_target(renderer* r, d3d_device_ptr device, size_type width, size_type height);
	size_type width() const;
	size_type height() const;
	size_type size() const;
	void copy_data(pointer);
private:
	void on_loss();
	void on_reset();

	void init();

	d3d_texture_ptr  tex;
	d3d_device_ptr   device;
	d3d_surface_ptr  surface;
	size_type        _width;
	size_type        _height;
};

}
}

#endif
