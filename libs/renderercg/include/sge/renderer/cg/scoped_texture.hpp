//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CG_SCOPED_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_CG_SCOPED_TEXTURE_HPP_INCLUDED

#include <sge/renderer/cg/const_loaded_texture_ref.hpp>
#include <sge/renderer/cg/scoped_texture_fwd.hpp>
#include <sge/renderer/cg/detail/symbol.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::cg
{

class scoped_texture
{
	FCPPT_NONMOVABLE(
		scoped_texture
	);
public:
	SGE_RENDERER_CG_DETAIL_SYMBOL
	scoped_texture(
		sge::renderer::context::core_ref,
		sge::renderer::cg::const_loaded_texture_ref
	);

	SGE_RENDERER_CG_DETAIL_SYMBOL
	~scoped_texture();

	[[nodiscard]]
	SGE_RENDERER_CG_DETAIL_SYMBOL
	sge::renderer::texture::stage
	stage() const;
private:
	sge::renderer::context::core_ref const context_;

	sge::renderer::cg::const_loaded_texture_ref const texture_;

	sge::renderer::texture::stage const stage_;
};

}

#endif
