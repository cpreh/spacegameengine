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


#ifndef SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_VOLUME_HPP_INCLUDED

#include "basic.hpp"
#include "volume_basic.hpp"
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

class volume
:
	public texture::volume_basic
{
	FCPPT_NONCOPYABLE(
		volume
	);
public:
	volume(
		IDirect3DDevice9 *,
		renderer::texture::volume_parameters const &
	);

	~volume();

	dim const
	size() const;

	view const
	lock(
		lock_area const &,
		renderer::lock_mode::type
	);

	const_view const
	lock(
		lock_area const &
	) const;

	void
	unlock() const;
private:
	volume_basic::lock_function const
	lock_function() const;
};

}
}
}

#endif
