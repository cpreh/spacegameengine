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


#ifndef SGE_RENDERER_GLSL_UNIFORM_DETAIL_BASIC_VALUE_IMPL_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_DETAIL_BASIC_VALUE_IMPL_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/detail/basic_value.hpp>
#include <sge/container/raw_vector_impl.hpp>

template<
	typename Value,
	typename Type
>
sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::basic_value(
	data_type const &data_,
	size_type const elements_,
	Type const type_)
:
	data_(data_),
	elements_(elements_),
	type_(type_)
{}

template<
	typename Value,
	typename Type
>
typename sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::const_pointer
sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::data() const
{
	return data_.data();
}

template<
	typename Value,
	typename Type
>
typename sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::pointer
sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::data()
{
	return data_.data();
}

template<
	typename Value,
	typename Type
>
sge::renderer::size_type
sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::elements() const
{
	return elements_;
}

template<
	typename Value,
	typename Type
>
Type
sge::renderer::glsl::uniform::detail::basic_value<Value, Type>::type() const
{
	return type_;
}

#endif
