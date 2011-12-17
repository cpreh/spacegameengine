/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_MUXING_STREAMBUF_DECL_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_DECL_HPP_INCLUDED

#include <sge/console/muxing.hpp>
#include <sge/console/muxing_streambuf_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
/**
\brief Multiplex the output of an ostream to the console and to the original target
\tparam Char The character type
\tparam Traits The according char traits

There are situations where you want to know the output of an ostream (for
example: std::cout, fcppt::io::cout, std::cerr and so on), but do not have a
terminal window to look at (since you're running in full-screen mode, for example).

A console (an sge::console::object, to be precise), might be present, however.
So it would be great if you could redirect the output of the given ostream to
the console. This is what the muxing_streambuf does.
*/
template<typename Char,typename Traits>
class muxing_streambuf
:
		std::basic_streambuf<Char,Traits>
{
FCPPT_NONCOPYABLE(
	muxing_streambuf);
public:
	typedef
	std::basic_streambuf<Char,Traits>
	streambuf_base;

	// This is just here to help MSVC++ resolve the int_type (crappy
	// compiler)
	typedef typename
	streambuf_base::int_type
	int_type;

	SGE_CONSOLE_SYMBOL explicit
	muxing_streambuf(
		std::basic_ostream<Char,Traits> &,
		sge::console::object &,
		console::muxing::type);

	SGE_CONSOLE_SYMBOL ~muxing_streambuf();
private:
	bool in_progress_;
	sge::console::object &object_;
	std::basic_ostream<Char,Traits> &stream_;
	std::basic_streambuf<Char,Traits> *old_streambuf_;
	console::muxing::type does_muxing_;
	std::basic_string<Char,Traits> buffer_;

	int_type
	overflow(
		int_type);

	static fcppt::string
	from_string(
		std::string const &);

	static fcppt::string
	from_string(
		std::wstring const &);
};
}
}

#endif
