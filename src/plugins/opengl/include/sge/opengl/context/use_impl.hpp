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


#ifndef SGE_OPENGL_CONTEXT_USE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_USE_IMPL_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/make_object.hpp>
#include <sge/opengl/context/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type,
	typename Domain,
	typename Parameter
>
Type &
use_impl(
	sge::opengl::context::object<
		Domain
	> &_object,
	Parameter &&_parameter
)
{
	typedef sge::opengl::context::base<
		Domain
	> base_type;

	base_type *ptr(
		_object.get(
			Type::static_id
		)
	);

	return
		ptr
		!=
		nullptr
		?
			static_cast<
				Type &
			>(
				*ptr
			)
		:
			static_cast<
				Type &
			>(
				_object.insert(
					Type::static_id,
					sge::opengl::context::make_object<
						Type,
						Domain
					>(
						_parameter
					)
				)
			)
		;
}

}
}
}

#endif
