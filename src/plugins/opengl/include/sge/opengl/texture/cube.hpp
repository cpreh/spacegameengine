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


#ifndef SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/cube_basic.hpp>
#include <sge/opengl/texture/cube_config_fwd.hpp>
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/container/enum_array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class cube
:
	public sge::opengl::texture::cube_basic
{
	FCPPT_NONCOPYABLE(
		cube
	);
public:
	cube(
		sge::opengl::texture::cube_config const &,
		sge::opengl::texture::basic_parameters const &,
		sge::renderer::texture::cube_parameters const &
	);

	~cube()
	override;
private:
	sge::opengl::texture::cube::size_type
	border_size() const
	override;

	sge::renderer::texture::cube::color_buffer &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	)
	override;

	sge::renderer::texture::cube::color_buffer const &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) const
	override;

	sge::renderer::texture::mipmap::level_count
	levels() const
	override;

	sge::renderer::texture::cube::size_type const size_;

	typedef
	fcppt::unique_ptr<
		sge::renderer::texture::cube::color_buffer
	>
	color_buffer_unique_ptr;

	typedef
	std::vector<
		color_buffer_unique_ptr
	>
	buffer_vector;

	typedef
	fcppt::container::enum_array<
		sge::renderer::texture::cube_side,
		buffer_vector
	>
	side_vector;

	side_vector sides_;
};

}
}
}

#endif
