/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_OPENGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_TEXTURE_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/opengl/detail/symbol.hpp>
#include <sge/renderer/opengl/texture/base_fwd.hpp>
#include <sge/renderer/opengl/texture/id.hpp>
#include <sge/renderer/opengl/texture/type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace opengl
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	base();
public:
	virtual
	sge::renderer::opengl::texture::id
	id() const = 0;

	virtual
	sge::renderer::opengl::texture::type
	type() const = 0;

	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	virtual
	~base();
};

}
}
}
}

#endif
