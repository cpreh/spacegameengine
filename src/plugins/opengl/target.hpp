/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_OPENGL_TARGET_HPP_INCLUDED
#define SGE_OPENGL_TARGET_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/target.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/container/raw_vector_decl.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace ogl
{

class target : public sge::renderer::target {
	SGE_NONCOPYABLE(target)
protected:
	target();
public:
	virtual void bind_me() const = 0;
	virtual ~target();
private:
	renderer::const_image_view const lock(
		renderer::lock_rect const &dest) const;
	void unlock() const;

	virtual renderer::pixel_pos const pos() const = 0;
	virtual size_type stride() const = 0;
	virtual GLenum format() const = 0;
	virtual GLenum format_type() const = 0;

	typedef sge::container::raw_vector<
		unsigned char
	> buffer_type;

	mutable buffer_type buffer;
};

}
}

#endif
