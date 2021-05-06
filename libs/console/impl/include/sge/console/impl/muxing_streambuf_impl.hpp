//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_IMPL_MUXING_STREAMBUF_IMPL_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_MUXING_STREAMBUF_IMPL_HPP_INCLUDED

#include <sge/console/muxing.hpp>
#include <sge/console/muxing_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/impl/from_string.hpp>
#include <fcppt/reference_impl.hpp>
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
	fcppt::reference<
		std::basic_ostream<
			Char,
			Traits
		>
	> const _stream,
	sge::console::object_ref const _object,
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
		stream_.get().rdbuf(
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

namespace sge::console
{
template<
	typename Char,
	typename Traits
>
muxing_streambuf<
	Char,
	Traits
>::~muxing_streambuf()
{
	stream_.get().rdbuf(
		old_streambuf_.release_ownership()
	);
}
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
	{
		return
			streambuf_base::traits_type::not_eof(
				_char
			);
	}

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
			stream_.get().widen(
				'\n'
			)
		)
		{
			object_.get().emit_message(
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
