/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/texture/cube_fwd.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
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
	SGE_SYMBOL cube();
public:
	typedef lock_rect rect_type;

	SGE_SYMBOL image2d::view::object const
	lock(
		texture::cube_side::type side,
		lock_mode::type
	);

	SGE_SYMBOL image2d::view::const_object const
	lock(
		texture::cube_side::type side
	) const;

	virtual image2d::view::object const
	lock(
		texture::cube_side::type,
		lock_rect const &,
		lock_mode::type
	) = 0;

	virtual image2d::view::const_object const
	lock(
		texture::cube_side::type,
		lock_rect const &
	) const = 0;

	virtual void
	unlock() const = 0;

	SGE_SYMBOL size_type
	content() const;

	SGE_SYMBOL rect_type const
	rect() const;

	virtual size_type
	border_size() const = 0;

	SGE_SYMBOL
	virtual ~cube();
};

}
}
}

#endif
