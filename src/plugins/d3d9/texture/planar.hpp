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


#ifndef SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED

#include "basic.hpp"
#include "planar_basic.hpp"
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

class planar
:
	public texture::planar_basic
{
	FCPPT_NONCOPYABLE(
		planar
	);
public:
	planar(
		IDirect3DDevice9 *,
		renderer::texture::planar_parameters const &
	);

	~planar();

	dim const
	size() const;

	view const
	lock(
		renderer::lock_rect const &,
		renderer::lock_mode::type
	);

	const_view const
	lock(
		renderer::lock_rect const &
	) const;

	void
	unlock() const;

	renderer::color_surface_ptr const
	surface(
		renderer::stage
	);

	sge::renderer::stage const
	stages() const;
private:
	planar_basic::lock_function const
	lock_function() const;
};

}
}
}

#endif
