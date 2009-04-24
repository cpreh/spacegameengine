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
#include "../../../error.hpp"
#include <boost/variant/apply_visitor.hpp>

#include <sge/text.hpp>
#include <sge/exception.hpp>

template<bool Native>
sge::ogl::glsl::attribute::variable<Native>::variable(
	handle const program,
	renderer::glsl::string const &name)
:
	location(
		attribute::location<Native>(
			program,
			name.c_str())),
	stored_type(
		type::nothing)
{}

template<bool Native>
sge::renderer::glsl::attribute::value const
sge::ogl::glsl::attribute::variable<Native>::get() const
{
	// FIXME
	throw exception(
		SGE_TEXT("unimplemented!"));
}

template<bool Native>
void sge::ogl::glsl::attribute::variable<Native>::set(
	renderer::glsl::attribute::value const &v)
{
	SGE_OPENGL_SENTRY
	stored_type = boost::apply_visitor(
		setter(
			location),
		v);
}

template class sge::ogl::glsl::attribute::variable<true>;
template class sge::ogl::glsl::attribute::variable<false>;
