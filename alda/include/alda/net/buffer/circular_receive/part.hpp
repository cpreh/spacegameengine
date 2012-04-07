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


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class part
{
	FCPPT_NONASSIGNABLE(
		part
	);
public:
	typedef alda::net::value_type *pointer;

	typedef alda::net::size_type size_type;

	ALDA_SYMBOL
	part(
		pointer begin,
		pointer end
	);

	ALDA_SYMBOL
	pointer
	begin() const;

	ALDA_SYMBOL
	pointer
	end() const;

	ALDA_SYMBOL
	size_type
	size() const;

	ALDA_SYMBOL
	bool
	empty() const;
private:
	pointer const
		begin_,
		end_;
};

}
}
}
}

#endif
