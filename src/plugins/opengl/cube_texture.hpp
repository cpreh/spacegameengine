/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_CUBE_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "basic_texture.hpp"
#include "context/object_fwd.hpp"
#include <sge/renderer/cube_texture.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opengl
{

namespace detail
{

typedef basic_texture<
	renderer::cube_texture
> cube_texture_base;

}

class cube_texture
:
	public detail::cube_texture_base
{
	FCPPT_NONCOPYABLE(cube_texture)
public:
	cube_texture(
		context::object &,
		size_type border_size,
		image::color::format::type format,
		renderer::filter::texture const &,
		renderer::resource_flags_field const &
	);

	~cube_texture();

	image2d::view::object const
	lock(
		renderer::cube_side::type side,
		renderer::lock_rect const &,
		renderer::lock_mode::type
	);

	image2d::view::const_object const
	lock(
		renderer::cube_side::type side,
		renderer::lock_rect const &
	) const;

	void
	unlock() const;

	size_type
	border_size() const;
private:
	void
	check_locked() const;

	void
	check_not_locked() const;

	size_type const size_;

	mutable renderer::texture *locked_texture_;

	typedef boost::ptr_vector<
		renderer::texture
	> texture_vector;

	mutable texture_vector textures_;
};

}
}

#endif
