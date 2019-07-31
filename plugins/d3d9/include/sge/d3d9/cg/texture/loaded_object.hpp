//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED
#define SGE_D3D9_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/parameter/object.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/base_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace cg
{
namespace texture
{

class loaded_object
:
	public sge::renderer::cg::loaded_texture
{
	FCPPT_NONCOPYABLE(
		loaded_object
	);
public:
	loaded_object(
		IDirect3DDevice9 &,
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &,
		sge::renderer::caps::texture_stages
	);

	~loaded_object();

	sge::renderer::texture::stage const
	activate() const;

	void
	deactivate() const;
private:
	IDirect3DDevice9 &device_;

	sge::cg::parameter::object const parameter_;

	sge::d3d9::texture::base const &texture_;

	sge::renderer::caps::texture_stages const texture_stages_;
};

}
}
}
}

#endif
