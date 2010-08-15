/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED

#include <sge/renderer/cube_side.hpp>
#include <sge/renderer/texture_base.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL cube_texture
:
	public texture_base
{
	FCPPT_NONCOPYABLE(cube_texture)
protected:
	SGE_SYMBOL cube_texture();
public:
	typedef lock_rect rect_type;

	SGE_SYMBOL image::view::object const
	lock(
		cube_side::type side,
		lock_mode::type
	);

	SGE_SYMBOL image::view::const_object const
	lock(
		cube_side::type side
	) const;

	virtual image::view::object const lock(
		cube_side::type side,
		lock_rect const &,
		lock_mode::type
	) = 0;

	virtual image::view::const_object const
	lock(
		cube_side::type side,
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
	virtual ~cube_texture();
};

}
}

#endif
