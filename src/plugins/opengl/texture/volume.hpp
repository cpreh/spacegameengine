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


#ifndef SGE_OPENGL_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_HPP_INCLUDED

#include "basic.hpp"
#include "scoped_work_bind_fwd.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

namespace detail
{

typedef texture::basic<
	renderer::texture::volume
> volume_texture_base;

}

class volume
:
	public detail::volume_texture_base
{
	FCPPT_NONCOPYABLE(
		volume
	);
public:
	typedef detail::volume_texture_base base;

	volume(
		opengl::context::object &,
		renderer::texture::volume_parameters const &
	);

	~volume();
private:
	typedef base::pointer pointer;

	void
	set_area(
		opengl::texture::scoped_work_bind const &,
		lock_area const &,
		pointer
	) const;
};

}
}
}

#endif