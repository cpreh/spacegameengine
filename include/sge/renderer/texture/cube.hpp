/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_TEXTURE_CUBE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CUBE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/cube_fwd.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CLASS_SYMBOL cube
:
	public renderer::texture::base
{
	FCPPT_NONCOPYABLE(
		cube
	);
protected:
	SGE_RENDERER_SYMBOL
	cube();
public:
	typedef renderer::lock_rect rect;

	typedef rect lock_area;

	typedef sge::image2d::tag image_tag;

	typedef image2d::view::object view;

	typedef image2d::view::const_object const_view;

	SGE_RENDERER_SYMBOL
	view const
	lock(
		texture::cube_side::type,
		lock_mode::type
	);

	SGE_RENDERER_SYMBOL
	const_view const
	lock(
		texture::cube_side::type
	) const;

	virtual view const
	lock(
		texture::cube_side::type,
		lock_area const &,
		lock_mode::type
	) = 0;

	virtual const_view const
	lock(
		texture::cube_side::type,
		lock_area const &
	) const = 0;

	virtual void
	unlock() const = 0;

	SGE_RENDERER_SYMBOL size_type
	content() const;

	SGE_RENDERER_SYMBOL
	rect const
	area() const;

	virtual size_type
	border_size() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~cube() = 0;
};

}
}
}

#endif
