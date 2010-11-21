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


#ifndef SGE_RENDERER_DEPTH_STENCIL_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_TEXTURE_HPP_INCLUDED

#include <sge/renderer/depth_stencil_texture_fwd.hpp>
#include <sge/renderer/texture_base.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL depth_stencil_texture
:
	public renderer::texture_base
{
	FCPPT_NONCOPYABLE(depth_stencil_texture)
protected:
	SGE_SYMBOL depth_stencil_texture();
public:
	SGE_SYMBOL virtual ~depth_stencil_texture();

	typedef renderer::dim2 dim_type;

	virtual dim2 const
	dim() const = 0;

	SGE_SYMBOL size_type
	content() const;

	virtual void
	debug() = 0; // TODO: remove this!
};

}
}

#endif
