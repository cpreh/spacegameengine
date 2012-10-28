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


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_OBJECT_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_OBJECT_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/join.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);

	typedef fcppt::container::raw_vector<
		alda::net::value_type
	> impl_type;
public:
	typedef alda::net::size_type size_type;

	typedef alda::net::value_type *pointer;

	typedef alda::net::value_type const *const_pointer;

	ALDA_SYMBOL
	explicit
	object(
		alda::net::buffer::max_receive_size
	);

	ALDA_SYMBOL
	~object();

	// To which part can we receive next?
	ALDA_SYMBOL
	alda::net::buffer::circular_receive::part const
	next_receive_part();

	// Tell the buffer how much was actually read
	ALDA_SYMBOL
	void
	bytes_received(
		size_type
	);

	typedef boost::iterator_range<
		const_pointer
	> iterator_range;

	typedef boost::joined_range<
		iterator_range const,
		iterator_range const
	> joined_range;

	// the range that can be read
	ALDA_SYMBOL
	joined_range const
	range() const;

	// remove already processed data
	ALDA_SYMBOL
	void
	erase(
		size_type
	);

	ALDA_SYMBOL
	size_type
	read_size() const;

	ALDA_SYMBOL
	size_type
	capacity() const;

	ALDA_SYMBOL
	void
	clear();
private:
	impl_type impl_;

	pointer
		begin_,
		end_;
};

}
}
}
}

#endif
