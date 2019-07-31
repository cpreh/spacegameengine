//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CG_SCOPED_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_CG_SCOPED_TEXTURE_HPP_INCLUDED

#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#include <sge/renderer/cg/scoped_texture_fwd.hpp>
#include <sge/renderer/cg/detail/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace cg
{

class scoped_texture
{
	FCPPT_NONCOPYABLE(
		scoped_texture
	);
public:
	SGE_RENDERER_CG_DETAIL_SYMBOL
	scoped_texture(
		sge::renderer::context::core &,
		sge::renderer::cg::loaded_texture const &
	);

	SGE_RENDERER_CG_DETAIL_SYMBOL
	~scoped_texture();

	SGE_RENDERER_CG_DETAIL_SYMBOL
	sge::renderer::texture::stage
	stage() const;
private:
	sge::renderer::context::core &context_;

	sge::renderer::cg::loaded_texture const &texture_;

	sge::renderer::texture::stage const stage_;
};

}
}
}

#endif
