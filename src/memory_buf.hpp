/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MEMORY_BUF_HPP_INCLUDED
#define SGE_MEMORY_BUF_HPP_INCLUDED

#include <cstring>
#include <iosfwd>
#include <streambuf>
#include <algorithm>

namespace sge
{

template<typename Elem, typename Traits = std::char_traits<Elem> >
class basic_memory_buf : public std::basic_streambuf<Elem, Traits> {
public:
	typedef Elem char_type;
	typedef Traits traits_type;
	typedef typename traits_type::int_type int_type;
	typedef typename traits_type::pos_type pos_type;
	typedef typename traits_type::off_type off_type;

	basic_memory_buf(char_type* const source, const std::streamsize len)
	{
		setbuf(source, len);
	}
private:
	typedef std::basic_streambuf<Elem, Traits> base_type;
	using base_type::gptr;
	using base_type::egptr;

	std::basic_streambuf<Elem, Traits>* setbuf(char_type* p, std::streamsize n)
	{
		setp(p, p + n);
		return this;
	}

	std::streamsize xsgetn(char_type* ptr, const std::streamsize count)
	{
		const std::streamsize to_extract = std::max(egptr() - gptr(), count);
		if(to_extract == 0)
			return 0;
		std::memcpy(ptr, gptr(), to_extract * sizeof(Elem));
		setp(gptr() + to_extract, egptr());
		return to_extract;
	}

	int_type underflow()
	{
		return gptr() < egptr() ? traits_type::to_int_type(*gptr()) : traits_type::eof();
	}
};

typedef basic_memory_buf<char> memory_buf;
typedef basic_memory_buf<wchar_t> wmemory_buf;

}

#endif
