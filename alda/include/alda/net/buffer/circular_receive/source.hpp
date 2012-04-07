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


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_SOURCE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_SOURCE_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class receive_buffer_source
{
	FCPPT_NONASSIGNABLE(
		receive_buffer_source
	);
public:
	typedef
	alda::net::value_type char_type;

	struct category
	:
		boost::iostreams::input_seekable,
		boost::iostreams::device_tag
	{
	};

	explicit
	receive_buffer_source(
		alda::net::buffer::circular_receive::object &
	);

	std::streamsize
	read(
		char *,
		std::streamsize
	);

	std::streampos
	seek(
		boost::iostreams::stream_offset,
		std::ios_base::seekdir
	);
private:
	alda::net::buffer::circular_receive::object &container_;

	std::streampos read_count_;
};

}
}
}
}

#endif
