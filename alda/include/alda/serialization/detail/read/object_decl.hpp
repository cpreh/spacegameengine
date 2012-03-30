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


#ifndef ALDA_SERIALIZATION_DETAIL_READ_OBJECT_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_OBJECT_DECL_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/read/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace read
{

template<
	typename TypeEnum
>
class object
{
	FCPPT_NONASSIGNABLE(
		object
	);
public:
	typedef typename alda::message::base_unique_ptr<
		TypeEnum
	>::type message_unique_ptr;

	explicit
	object(
		alda::serialization::istream &
	);

	template<
		typename Message
	>
	message_unique_ptr
	operator()() const;
private:
	alda::serialization::istream &stream_;
};

}
}
}
}

#endif
