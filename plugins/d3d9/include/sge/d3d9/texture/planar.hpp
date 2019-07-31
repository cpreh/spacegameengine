//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_PLANAR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/planar_basic.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

class planar
:
	public sge::d3d9::texture::planar_basic
{
	FCPPT_NONCOPYABLE(
		planar
	);
public:
	planar(
		IDirect3DDevice9 &,
		sge::renderer::texture::planar_parameters const &
	);

	~planar()
	override;
private:
	sge::renderer::texture::planar::nonconst_buffer &
	level(
		sge::renderer::texture::mipmap::level
	)
	override;

	sge::renderer::texture::planar::const_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const
	override;

	sge::d3d9::surface::d3d_unique_ptr
	get_level(
		sge::renderer::texture::mipmap::level
	);

	typedef
	std::vector<
		fcppt::unique_ptr<
			sge::renderer::texture::planar::nonconst_buffer
		>
	>
	level_vector;

	level_vector const levels_;
};

}
}
}

#endif
