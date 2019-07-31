//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/cube_basic.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

class cube
:
	public sge::d3d9::texture::cube_basic
{
	FCPPT_NONCOPYABLE(
		cube
	);
public:
	cube(
		IDirect3DDevice9 &,
		sge::renderer::texture::cube_parameters const &
	);

	~cube()
	override;
private:
	sge::renderer::size_type
	border_size() const
	override;

	sge::renderer::texture::cube::nonconst_buffer &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	)
	override;

	sge::renderer::texture::cube::const_buffer const &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) const
	override;

	sge::d3d9::surface::d3d_unique_ptr
	get_level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	);

	typedef
	std::vector<
		fcppt::unique_ptr<
			sge::renderer::texture::cube::nonconst_buffer
		>
	>
	level_vector;

	typedef
	fcppt::enum_::array<
		sge::renderer::texture::cube_side,
		level_vector
	>
	side_array;

	side_array const sides_;
};

}
}
}

#endif
