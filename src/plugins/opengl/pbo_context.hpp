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


#ifndef SGE_OPENGL_PBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_PBO_CONTEXT_HPP_INCLUDED

#include "vbo_base_fwd.hpp"
#include "context/base.hpp"
#include "context/id.hpp"
#include "common.hpp"
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class pbo_context
:
	public context::base
{
	FCPPT_NONCOPYABLE(pbo_context)
public:
	pbo_context();

	~pbo_context();
	
	vbo_base &
	impl();

	GLenum
	pixel_pack_buffer_type() const;

	GLenum
	pixel_unpack_buffer_type() const;

	typedef void needs_before;

	static context::id const static_id;
private:
	fcppt::scoped_ptr<
		vbo_base
	> impl_;

	GLenum const
		pixel_pack_buffer_type_,
		pixel_unpack_buffer_type_;
};

}
}

#endif
