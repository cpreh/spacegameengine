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


#ifndef SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED

#include "basic.hpp"
#include "cube_basic.hpp"
#include "../d3dinclude.hpp"
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

namespace sge
{
namespace d3d9
{
namespace texture
{

class cube
:
	public texture::cube_basic
{
	FCPPT_NONCOPYABLE(
		cube
	);
public:
	cube(
		IDirect3DDevice9 *,
		renderer::texture::cube_parameters const &
	);

	~cube();
public:
	view const
	lock(
		renderer::texture::cube_side::type,
		renderer::lock_rect const &,
		renderer::lock_mode::type
	);

	const_view const
	lock(
		renderer::texture::cube_side::type,
		renderer::lock_rect const &
	) const;

	void
	unlock() const;

	size_type
	border_size() const;
private:
	cube_basic::lock_function const
	lock_function(
		renderer::texture::cube_side::type
	) const;

	typedef fcppt::optional<
		renderer::texture::cube_side::type
	> optional_cube_side;

	mutable optional_cube_side locked_side_;
};

}
}
}

#endif
