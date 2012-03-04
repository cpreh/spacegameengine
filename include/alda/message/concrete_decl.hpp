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


#ifndef ALDA_MESSAGE_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_MESSAGE_CONCRETE_DECL_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace message
{

template<
	typename TypeEnum,
	typename Type
>
class concrete
:
	public alda::message::base<
		TypeEnum
	>
{
	FCPPT_NONCOPYABLE(
		concrete
	);

	typedef alda::message::base<
		TypeEnum
	> base_type;
public:
	typedef typename base_type::type_enum type_enum;

	explicit
	concrete(
		Type const &
	);

	~concrete();

	Type const &
	value() const;
private:
	typedef typename base_type::const_raw_pointer const_raw_pointer;

	typedef typename base_type::size_type size_type;

	type_enum
	type() const;

	const_raw_pointer
	data() const;

	size_type
	size() const;

	Type value_;
};

}
}

#endif
