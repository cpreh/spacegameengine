/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/iconv/object.hpp>
#include <sge/iconv/exception.hpp>
#include <sge/iconv/unsupported_conversion.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <iconv.h>
#include <cstddef>
#include <cerrno>

class sge::iconv::object::impl
{
	FCPPT_NONCOPYABLE(
		impl
	)
public:
	impl(
		sge::iconv::encoding_string const &source,
		sge::iconv::encoding_string const &dest
	);

	~impl();

	::iconv_t iconv_;
};

sge::iconv::object::object(
	iconv::encoding_string const &_source,
	iconv::encoding_string const &_dest
)
:
	impl_(
		fcppt::make_unique_ptr<
			impl
		>(
			_source,
			_dest
		)
	)
{
}

sge::iconv::object::~object()
{
}

sge::iconv::conversion_status::type
sge::iconv::object::convert(
	iconv::const_raw_pointer &_source,
	iconv::size_type &_in_bytes_left,
	iconv::raw_pointer &_dest,
	iconv::size_type &_out_bytes_left
)
{
	::size_t const ret(
		::iconv(
			impl_->iconv_,
			// TODO: check if this is really needed!
			const_cast<
				char **
			>(
				&_source
			),
			&_in_bytes_left,
			&_dest,
			&_out_bytes_left
		)
	);

	if(
		ret
		!= static_cast<
			std::size_t
		>(
			-1
		)
	)
		return iconv::conversion_status::ok;
	
	switch(
		errno
	)
	{
	case E2BIG:
		return iconv::conversion_status::output_too_small;
	case EILSEQ:
		return iconv::conversion_status::invalid_sequence;
	case EINVAL:
		return iconv::conversion_status::incomplete_input;
	default:
		throw sge::iconv::exception(
			FCPPT_TEXT(
				"Invalid errno on iconv error!"
			)
		);
	}
}

sge::iconv::object::impl::impl(
	sge::iconv::encoding_string const &_source,
	sge::iconv::encoding_string const &_dest
)
:
	iconv_(
		::iconv_open(
			_dest.c_str(),
			_source.c_str()
		)
	)
{
	if(
		iconv_
		== reinterpret_cast<
			::iconv_t
		>(
			-1
		)
	)
		throw sge::iconv::unsupported_conversion(
			_source,
			_dest
		);
}

sge::iconv::object::impl::~impl()
{
	::iconv_close(
		iconv_
	);
}
