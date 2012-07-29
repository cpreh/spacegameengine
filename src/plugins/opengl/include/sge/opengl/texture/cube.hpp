/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class cube
:
	public sge::renderer::texture::cube,
	public sge::opengl::texture::base
{
	FCPPT_NONCOPYABLE(
		cube
	);
public:
	cube(
		sge::opengl::texture::basic_parameters const &,
		sge::renderer::texture::cube_parameters const &
	);

	~cube();

	sge::opengl::texture::cube::size_type
	border_size() const;

	sge::renderer::texture::cube::color_buffer &
	level(
		sge::renderer::texture::cube_side::type,
		sge::renderer::texture::mipmap::level
	);

	sge::renderer::texture::cube::color_buffer const &
	level(
		sge::renderer::texture::cube_side::type,
		sge::renderer::texture::mipmap::level
	) const;

	sge::renderer::texture::mipmap::level_count const
	levels() const;

	sge::renderer::resource_flags_field const
	resource_flags() const;

	sge::renderer::texture::capabilities_field const
	capabilities() const;
private:
	sge::renderer::texture::mipmap::object const
	mipmap() const;

	sge::renderer::texture::planar const &
	ref_texture() const;

	sge::opengl::texture::cube::size_type const size_;

	mutable sge::renderer::texture::planar *locked_texture_;

	typedef boost::ptr_vector<
		sge::renderer::texture::planar
	> texture_vector;

	mutable sge::opengl::texture::cube::texture_vector textures_;
};

}
}
}

#endif
