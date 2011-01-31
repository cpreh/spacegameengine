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


#ifndef SGE_RENDERER_COLOR_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_COLOR_SURFACE_HPP_INCLUDED

#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL color_surface
{
	FCPPT_NONCOPYABLE(
		color_surface
	)
protected:
	SGE_SYMBOL
	color_surface();
public:
	SGE_SYMBOL
	virtual ~color_surface();

	typedef renderer::size_type size_type;

	typedef renderer::dim2 dim_type;

	typedef renderer::lock_rect rect_type;
	
	SGE_SYMBOL
	image2d::view::const_object const
	lock() const;

	virtual image2d::view::const_object const
	lock(
		lock_rect const &
	) const = 0;

	virtual void
	unlock() const = 0;

	virtual dim_type const
	dim() const = 0;

	SGE_SYMBOL
	rect_type const
	rect() const;

	SGE_SYMBOL
	size_type
	size() const;
};

}
}

#endif
