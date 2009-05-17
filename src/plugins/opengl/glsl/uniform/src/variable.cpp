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



#include "../variable.hpp"
#include "../variable_functions.hpp"
#include "../setter.hpp"
#include "../get.hpp"
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>

template<
	bool Native
>
sge::ogl::glsl::uniform::variable<Native>::variable(
	handle const program,
	renderer::glsl::string const &name)
:
	program(
		program
	),
	location(
		uniform::location<Native>(
			program,
			name.c_str()
		)
	),
	stored_type(
		element_type::nothing,
		0
	)
{}

template<
	bool Native
>
sge::renderer::glsl::uniform::value const
sge::ogl::glsl::uniform::variable<Native>::get() const
{
	return uniform::get<Native>(
		program,
		location,
		stored_type
	);
}

template<
	bool Native
>
void sge::ogl::glsl::uniform::variable<Native>::set(
	renderer::glsl::uniform::value const &v)
{
	stored_type = variant::apply_unary(
		setter(
			location
		),
		v
	);
}

template class sge::ogl::glsl::uniform::variable<true>;
template class sge::ogl::glsl::uniform::variable<false>;
