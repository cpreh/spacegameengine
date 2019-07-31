//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Tag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL basic_lockable_box
:
	public sge::renderer::texture::base
{
	FCPPT_NONCOPYABLE(
		basic_lockable_box
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	basic_lockable_box();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~basic_lockable_box()
	override;

	typedef
	sge::image::dim<
		Tag
	>
	dim;

	typedef
	sge::renderer::buffer::readable<
		Tag
	>
	const_buffer;

	typedef
	sge::renderer::buffer::writable<
		Tag
	>
	nonconst_buffer;

	SGE_RENDERER_DETAIL_SYMBOL
	dim
	size() const;

	virtual
	nonconst_buffer &
	level(
		sge::renderer::texture::mipmap::level
	) = 0;

	virtual
	const_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const = 0;
};

}
}
}

#endif
