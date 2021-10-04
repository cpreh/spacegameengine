//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/cube_basic_fwd.hpp>
#include <sge/opengl/texture/cube_config_fwd.hpp>
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::texture
{

class cube
:
	public sge::opengl::texture::cube_basic
{
	FCPPT_NONMOVABLE(
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
	[[nodiscard]]
	sge::renderer::size_type
	border_size() const
	override;

	[[nodiscard]]
	sge::renderer::texture::cube::nonconst_buffer &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	)
	override;

	[[nodiscard]]
	sge::renderer::texture::cube::const_buffer const &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) const
	override;

	[[nodiscard]]
	sge::renderer::texture::mipmap::level_count
	levels() const
	override;

	sge::renderer::size_type const size_;

	using
	buffer_unique_ptr
	=
	fcppt::unique_ptr<
		sge::renderer::texture::cube::nonconst_buffer
	>;

	using
	buffer_vector
	=
	std::vector<
		buffer_unique_ptr
	>;

	using
	side_array
	=
	fcppt::enum_::array<
		sge::renderer::texture::cube_side,
		buffer_vector
	>;

	side_array const sides_;
};

}

#endif
