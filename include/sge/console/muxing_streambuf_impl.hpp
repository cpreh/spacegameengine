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


#ifndef SGE_CONSOLE_MUXING_STREAMBUF_IMPL_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_IMPL_HPP_INCLUDED

#include <sge/console/muxing_streambuf_decl.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
template<typename Char,typename Traits>
sge::console::muxing_streambuf<Char,Traits>::muxing_streambuf(
	std::basic_ostream<Char,Traits> &_stream,
	sge::console::object &_object,
	console::muxing::type const _does_muxing)
:
	in_progress_(
		false),
	object_(
		_object),
	stream_(
		_stream),
	old_streambuf_(
		stream_.rdbuf(
			this)),
	does_muxing_(
		_does_muxing),
	buffer_()
{
}
FCPPT_PP_POP_WARNING

template<typename Char,typename Traits>
sge::console::muxing_streambuf<Char,Traits>::~muxing_streambuf()
{
	stream_.rdbuf(
		old_streambuf_);
}

template<typename Char,typename Traits>
typename sge::console::muxing_streambuf<Char,Traits>::int_type
sge::console::muxing_streambuf<Char,Traits>::overflow(
	int_type c)
{
	if(in_progress_)
		return
			streambuf_base::traits_type::not_eof(
				c);

	in_progress_ = true;

	if(does_muxing_ == muxing::enabled)
	{
		old_streambuf_->sputc(
			streambuf_base::traits_type::to_char_type(
				c));
	}

	if(c != streambuf_base::traits_type::eof())
	{
		if(streambuf_base::traits_type::to_char_type(c) == stream_.widen('\n'))
		{
			object_.emit_message(
				sge::font::text::from_fcppt_string(
					this->from_string(
						buffer_)));
			buffer_.clear();
		}
		else
		{
			buffer_ +=
				streambuf_base::traits_type::to_char_type(
					c);
		}
	}

	in_progress_ = false;

	return
		streambuf_base::traits_type::not_eof(
			c);
}

template<typename Char,typename Traits>
fcppt::string
sge::console::muxing_streambuf<Char,Traits>::from_string(
	std::string const &s)
{
	return
		fcppt::from_std_string(
			s);
}

template<typename Char,typename Traits>
fcppt::string
sge::console::muxing_streambuf<Char,Traits>::from_string(
	std::wstring const &s)
{
	return
		fcppt::from_std_wstring(
			s);
}

#endif
