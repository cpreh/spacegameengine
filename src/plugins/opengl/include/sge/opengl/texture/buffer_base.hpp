/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BUFFER_BASE_HPP_INCLUDED

#include <sge/opengl/texture/buffer_base_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class buffer_base
{
	FCPPT_NONCOPYABLE(
		buffer_base
	);
protected:
	buffer_base(
		sge::opengl::texture::buffer_type,
		sge::opengl::texture::id,
		sge::renderer::texture::mipmap::level
	);
public:
	virtual
	~buffer_base();

	sge::opengl::texture::buffer_type const
	buffer_type() const;

	sge::opengl::texture::id const
	id() const;

	sge::renderer::texture::mipmap::level const
	level() const;
private:
	sge::opengl::texture::buffer_type const buffer_type_;

	sge::opengl::texture::id const id_;

	sge::renderer::texture::mipmap::level const level_;
};

}
}
}

#endif
