#ifndef SGE_CONSOLE_MUXING_STREAMBUF_IMPL_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_IMPL_HPP_INCLUDED

#include <sge/console/muxing_streambuf_decl.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


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

template<typename Char,typename Traits>
sge::console::muxing_streambuf<Char,Traits>::~muxing_streambuf()
{
	stream_.rdbuf(
		old_streambuf_);
}

template<typename Char,typename Traits>
typename sge::console::muxing_streambuf<Char,Traits>::streambuf_base::int_type
sge::console::muxing_streambuf<Char,Traits>::overflow(
	typename streambuf_base::int_type const c)
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
