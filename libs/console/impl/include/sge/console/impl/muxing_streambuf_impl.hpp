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


#ifndef SGE_CONSOLE_IMPL_MUXING_STREAMBUF_IMPL_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_MUXING_STREAMBUF_IMPL_HPP_INCLUDED

#include <sge/console/muxing.hpp>
#include <sge/console/muxing_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/impl/from_string.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Char,
	typename Traits
>
sge::console::muxing_streambuf<
	Char,
	Traits
>::muxing_streambuf(
	std::basic_ostream<
		Char,
		Traits
	> &_stream,
	sge::console::object &_object,
	sge::console::muxing const _does_muxing
)
:
	streambuf_base(),
	in_progress_(
		false
	),
	object_(
		_object
	),
	stream_(
		_stream
	),
	old_streambuf_(
		stream_.rdbuf(
			this
		)
	),
	does_muxing_(
		_does_muxing
	),
	buffer_()
{
}
FCPPT_PP_POP_WARNING

template<
	typename Char,
	typename Traits
>
sge::console::muxing_streambuf<
	Char,
	Traits
>::~muxing_streambuf()
{
	stream_.rdbuf(
		old_streambuf_.release_ownership()
	);
}

template<
	typename Char,
	typename Traits
>
typename sge::console::muxing_streambuf<
	Char,
	Traits
>::int_type
sge::console::muxing_streambuf<
	Char,
	Traits
>::overflow(
	int_type const _char
)
{
	if(
		in_progress_
	)
		return
			streambuf_base::traits_type::not_eof(
				_char
			);

	in_progress_ =
		true;

	if(
		does_muxing_
		==
		sge::console::muxing::enabled
	)
	{
		old_streambuf_->sputc(
			streambuf_base::traits_type::to_char_type(
				_char
			)
		);
	}

	if(
		_char
		!=
		streambuf_base::traits_type::eof()
	)
	{
		if(
			streambuf_base::traits_type::to_char_type(
				_char
			)
			==
			stream_.widen(
				'\n'
			)
		)
		{
			object_.emit_message(
				sge::console::impl::from_string(
					buffer_
				)
			);

			buffer_.clear();
		}
		else
		{
			buffer_ +=
				streambuf_base::traits_type::to_char_type(
					_char
				);
		}
	}

	in_progress_ =
		false;

	return
		streambuf_base::traits_type::not_eof(
			_char
		);
}

#endif
