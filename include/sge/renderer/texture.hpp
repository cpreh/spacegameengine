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


#ifndef SGE_RENDERER_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_HPP_INCLUDED

#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture_base.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL texture
:
	public texture_base
{
	FCPPT_NONCOPYABLE(
		texture
	)
protected:
	SGE_SYMBOL texture();
public:
	SGE_SYMBOL virtual ~texture();

	typedef renderer::dim2 dim_type;

	typedef renderer::lock_rect rect_type;

	typedef rect_type lock_area;

	typedef sge::image2d::tag image_tag;

	typedef image2d::view::object view_type;

	typedef image2d::view::const_object const_view_type;

	virtual dim_type const
	dim() const = 0;

	SGE_SYMBOL view_type const
	lock(
		lock_mode::type
	);

	SGE_SYMBOL const_view_type const
	lock() const;

	virtual view_type const
	lock(
		lock_rect const &,
		lock_mode::type
	) = 0;

	virtual const_view_type const
	lock(
		lock_rect const &
	) const = 0;

	virtual void
	unlock() const = 0;

	virtual renderer::color_surface_ptr const
	surface(
		renderer::stage_type
	) = 0;

	virtual sge::renderer::stage_type
	stages() const = 0;

	SGE_SYMBOL
	rect_type const
	rect() const;

	SGE_SYMBOL
	rect_type const
	area() const;

	SGE_SYMBOL
	texture_base::size_type
	content() const;
};

}
}

#endif
