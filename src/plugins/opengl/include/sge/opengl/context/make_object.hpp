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


#ifndef SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_MAKE_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/dummy_parameter_fwd.hpp>
#include <sge/opengl/context/has_parameter.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
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
	typename Type
>
typename
boost::enable_if<
	sge::opengl::context::has_parameter<
		Type
	>,
	sge::opengl::context::base_unique_ptr
>::type
make_object(
	typename
	Type::parameter &_parameter
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::context::base
		>(
			fcppt::make_unique_ptr<
				Type
			>(
				_parameter
			)
		);
}

template<
	typename Type
>
typename
boost::disable_if<
	sge::opengl::context::has_parameter<
		Type
	>,
	sge::opengl::context::base_unique_ptr
>::type
make_object(
	sge::opengl::context::dummy_parameter const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::context::base
		>(
			fcppt::make_unique_ptr<
				Type
			>(
			)
		);
}

}
}
}

#endif
