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


#ifndef SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/traits/dim_fwd.hpp>
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
	override = 0;

	typedef
	typename
	sge::image::traits::dim<
		Tag
	>::type
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
