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


#ifndef SGE_RENDERER_TEXTURE_PLANAR_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_PLANAR_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/object_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CLASS_SYMBOL planar
:
	public renderer::texture::base
{
	FCPPT_NONCOPYABLE(
		planar
	);
protected:
	SGE_RENDERER_SYMBOL
	planar();
public:
	SGE_RENDERER_SYMBOL
	virtual ~planar();

	typedef renderer::dim2 dim;

	typedef renderer::lock_rect rect;

	typedef rect lock_area;

	typedef sge::image2d::tag image_tag;

	typedef image2d::view::object view;

	typedef image2d::view::const_object const_view;

	virtual dim const
	size() const = 0;

	SGE_RENDERER_SYMBOL
	view const
	lock(
		lock_mode::type
	);

	SGE_RENDERER_SYMBOL
	const_view const
	lock() const;

	virtual view const
	lock(
		lock_area const &,
		lock_mode::type
	) = 0;

	virtual const_view const
	lock(
		lock_area const &
	) const = 0;

	virtual void
	unlock() const = 0;

	virtual renderer::color_surface_ptr const
	surface(
		renderer::stage_type
	) = 0;

	virtual sge::renderer::stage_type
	stages() const = 0;

	SGE_RENDERER_SYMBOL
	rect const
	area() const;

	SGE_RENDERER_SYMBOL
	texture::base::size_type
	content() const;
};

}
}
}

#endif
