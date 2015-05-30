/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_BUFFER_PBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_PBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class pbo_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		pbo_context
	);
public:
	pbo_context();

	~pbo_context()
	override;

	sge::opengl::buffer::base &
	impl();

	sge::opengl::buffer::type const
	pixel_pack_buffer_type() const;

	sge::opengl::buffer::type const
	pixel_unpack_buffer_type() const;

	typedef void parameter;

	static sge::opengl::context::system::id const static_id;
private:
	fcppt::unique_ptr<
		sge::opengl::buffer::base
	> const impl_;

	sge::opengl::buffer::type const
		pixel_pack_buffer_type_,
		pixel_unpack_buffer_type_;
};

}
}
}

#endif
