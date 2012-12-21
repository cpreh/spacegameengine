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


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image/ds/format_fwd.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/view/const_object_fwd.hpp>
#include <sge/imageds2d/view/object_fwd.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace depth_stencil_buffer
{

/**
\brief Describes an abstraction of a depth stencil store

A depth stencil surface describes an abstraction of a depth stencil store. For
example, the every mipmap level of a sge::renderer::texture::depth_stencil is a
depth stencil surface. An sge::renderer::target::base (including the
sge::renderer::target::onscreen) can have a depth stencil surface as well.
*/
class SGE_CLASS_SYMBOL surface
{
	FCPPT_NONCOPYABLE(
		surface
	);
protected:
	SGE_RENDERER_SYMBOL
	surface();
public:
	// TODO: Unify this with color_buffer
	typedef sge::renderer::size_type size_type;

	/**
	\brief The dimension type

	Specifies a two dimensional size in pixels
	*/
	typedef sge::renderer::dim2 dim;

	typedef sge::renderer::lock_rect lock_area;

	typedef sge::imageds2d::tag image_tag;

	typedef sge::imageds2d::view::object view;

	typedef sge::imageds2d::view::const_object const_view;

	SGE_RENDERER_SYMBOL
	virtual
	~surface() = 0;

	/**
	\brief The size of the buffer

	\return The size of the buffer as a two dimensional size of pixels
	*/
	virtual
	dim const
	size() const = 0;

	SGE_RENDERER_SYMBOL
	lock_area const
	area() const;

	SGE_RENDERER_SYMBOL
	size_type
	content() const;

	/**
	\brief The format of the buffer
	*/
	virtual
	sge::image::ds::format
	format() const = 0;

	// TODO!
};

}
}
}

#endif
