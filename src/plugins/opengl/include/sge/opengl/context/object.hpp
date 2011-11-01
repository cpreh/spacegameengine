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


#ifndef SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/container.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object();

	~object();

	base *
	get(
		context::id
	);

	base &
	insert(
		context::id,
		base_unique_ptr
	);
private:
	typedef context::container container;

	container elements_;
};

}
}
}

#endif
