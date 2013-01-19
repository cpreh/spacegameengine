/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/opengl/context/dummy_parameter.hpp>
#include <sge/opengl/context/has_parameter.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Type,
	typename Domain
>
typename boost::disable_if<
	sge::opengl::context::has_parameter<
		Type
	>,
	Type &
>::type
use(
	sge::opengl::context::object<
		Domain
	> &_object
)
{
	return
		sge::opengl::context::use_impl<
			Type
		>(
			_object,
			sge::opengl::context::dummy_parameter()
		);
}

template<
	typename Type,
	typename Domain,
	typename Parameter
>
typename boost::enable_if<
	sge::opengl::context::has_parameter<
		Type
	>,
	Type &
>::type
use(
	sge::opengl::context::object<
		Domain
	> &_object,
	Parameter &&_parameter
)
{
	return
		sge::opengl::context::use_impl<
			Type
		>(
			_object,
			_parameter
		);

}

}
}
}

#endif
