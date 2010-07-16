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


#ifndef SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED

#include "use_fwd.hpp"
#include "base_auto_ptr.hpp"
#include "object_fwd.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type
>
typename boost::enable_if<
	boost::is_same<
		typename Type::needs_before,
		void
	>,
	base_auto_ptr
>::type
make_object(
	object &
)
{
	base_auto_ptr ret(
		fcppt::make_auto_ptr<
			Type
		>()
	);

	return ret;
}

template<
	typename Type
>
typename boost::disable_if<
	boost::is_same<
		typename Type::needs_before,
		void
	>,
	base_auto_ptr
>::type
make_object(
	object &_object
)
{
/*
	return
		fcppt::make_auto_ptr<
			Type
		>(
			std::tr1::ref(
				context::use<
					typename Type::needs_before
				>(
					_object
				)
			)
		);
*/
}

}
}
}

#endif
