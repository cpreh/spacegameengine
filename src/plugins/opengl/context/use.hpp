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


#ifndef SGE_OPENGL_CONTEXT_USE_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_USE_HPP_INCLUDED

#include "object.hpp"
#include "base_auto_ptr.hpp"
#include <fcppt/make_auto_ptr.hpp>

namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type
>
Type &
use(
	object &_object
)
{
	base *ptr(
		_object.get(
			Type::static_id
		)
	);

	if(
		ptr
	)
		return
			static_cast<
				Type &
			>(
				*ptr
			);
	
	base_auto_ptr new_ptr(
		fcppt::make_auto_ptr<
			Type
		>()
	);

	return
		static_cast<
			Type &
		>(
			_object.insert(
				Type::static_id,
				new_ptr
			)
		);
}

}
}
}

#endif
