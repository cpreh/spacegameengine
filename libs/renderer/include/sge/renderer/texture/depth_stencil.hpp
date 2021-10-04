//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/depth_stencil_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL depth_stencil
:
	public sge::renderer::texture::base
{
	FCPPT_NONMOVABLE(
		depth_stencil
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	depth_stencil();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~depth_stencil()
	override;

	using
	dim
	=
	sge::renderer::dim2;

	using
	const_buffer
	=
	sge::renderer::depth_stencil_buffer::surface;

	using
	nonconst_buffer
	=
	sge::renderer::depth_stencil_buffer::surface;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	dim
	size() const;

	[[nodiscard]]
	virtual
	nonconst_buffer &
	level(
		sge::renderer::texture::mipmap::level
	) = 0;

	[[nodiscard]]
	virtual
	const_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const = 0;
};

}

#endif
