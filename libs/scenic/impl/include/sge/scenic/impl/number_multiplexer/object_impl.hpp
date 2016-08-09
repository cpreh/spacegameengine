/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/object_decl.hpp>
#include <sge/scenic/impl/number_multiplexer/set_bits.hpp>
#include <fcppt/literal.hpp>


template<typename T>
sge::scenic::impl::number_multiplexer::object<T>::object()
:
	value_(
		fcppt::literal<value_type>(
			0)),
	last_bit_set_(
		fcppt::literal<value_type>(
			0))
{
}

template<typename T>
sge::scenic::impl::number_multiplexer::object<T>::object(
	value_type const _value)
:
	value_(
		_value),
	last_bit_set_(
		fcppt::literal<value_type>(
			0))
{
}

template<typename T>
sge::scenic::impl::number_multiplexer::object<T> &
sge::scenic::impl::number_multiplexer::object<T>::append(
	bit_count const &_bit_count,
	value_type const _value)
{
	value_ =
		sge::scenic::impl::number_multiplexer::set_bits(
			last_bit_set_,
			_bit_count.get(),
			_value,
			value_);

	last_bit_set_ +=
		_bit_count.get();

	return
		*this;
}

template<typename T>
typename
sge::scenic::impl::number_multiplexer::object<T>::value_type
sge::scenic::impl::number_multiplexer::object<T>::value() const
{
	return
		value_;
}

#endif
