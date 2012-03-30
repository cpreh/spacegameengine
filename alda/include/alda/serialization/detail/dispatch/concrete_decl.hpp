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


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_DECL_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace dispatch
{

template<
	typename TypeEnum,
	typename Message
>
class concrete
:
	public alda::serialization::detail::dispatch::base<
		TypeEnum
	>
{
	FCPPT_NONCOPYABLE(
		concrete
	);

	typedef alda::serialization::detail::dispatch::base<
		TypeEnum
	> base_type;
public:
	concrete();

	~concrete();

	typedef typename base_type::message_unique_ptr message_unique_ptr;

	typedef typename base_type::reader reader;

	message_unique_ptr
	on_dispatch(
		reader const &
	) const;
};

}
}
}
}

#endif
