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


#ifndef SGE_OPENGL_CONTEXT_MAKE_ID_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_MAKE_ID_HPP_INCLUDED

#include <sge/opengl/context/id_decl.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Domain
>
sge::opengl::context::id<
	Domain
> const
make_id()
{
	typedef
	sge::opengl::context::id<
		Domain
	>
	id_type;

	typedef typename id_type::type counter_type;

	static counter_type counter(0u);

	return
		id_type(
			++counter
		);
}

}
}
}

#endif
