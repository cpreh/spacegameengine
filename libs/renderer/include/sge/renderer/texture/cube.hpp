//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/color_buffer/writable_surface_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/cube_fwd.hpp>
#include <sge/renderer/texture/cube_side_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL cube
:
	public sge::renderer::texture::base
{
	FCPPT_NONMOVABLE(
		cube
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	cube();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~cube()
	override;

	using
	const_buffer
	=
	sge::renderer::color_buffer::readable_surface;

	using
	nonconst_buffer
	=
	sge::renderer::color_buffer::writable_surface;

	[[nodiscard]]
	virtual
	sge::renderer::size_type
	border_size() const = 0;

	[[nodiscard]]
	virtual
	nonconst_buffer &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) = 0;

	[[nodiscard]]
	virtual
	const_buffer const &
	level(
		sge::renderer::texture::cube_side,
		sge::renderer::texture::mipmap::level
	) const = 0;
};

}
}
}

#endif
