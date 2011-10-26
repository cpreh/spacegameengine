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


#ifndef SGE_OPENGL_GLSL_PROGRAM_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_HOLDER_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{

template<
	typename Environment
>
class program_holder
{
	FCPPT_NONCOPYABLE(
		program_holder
	);
public:
	typedef typename Environment::program_context program_context;

	typedef typename Environment::handle handle;

	explicit program_holder(
		opengl::context::object &
	);

	~program_holder();

	program_context const &
	context() const;

	handle
	id() const;
private:
	program_context const &context_;

	handle const id_;
};

}
}
}

#endif
