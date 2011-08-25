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


#ifndef SGE_RENDERER_TARGET_HPP_INCLUDED
#define SGE_RENDERER_TARGET_HPP_INCLUDED

#include <sge/renderer/target_fwd.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL target
:
	public sge::renderer::target_base
{
	FCPPT_NONCOPYABLE(
		target
	);
protected:
	SGE_RENDERER_SYMBOL
	target();
public:
	virtual void
	color_surface(
		renderer::color_surface_ptr,
		renderer::surface_index
	) = 0;

	virtual void
	depth_stencil_surface(
		renderer::depth_stencil_surface_ptr
	) = 0;

	virtual renderer::optional_dim2 const
	size() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~target() = 0;
};

}
}

#endif
