/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/charconv/char_type.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/conversion_failed.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <codecvt>
#include <locale>
#include <stdexcept>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	sge::charconv::encoding Encoding
>
using
converter_impl
=
std::wstring_convert<
	std::codecvt_utf8<
		sge::charconv::char_type<
			Encoding
		>
	>,
	sge::charconv::char_type<
		Encoding
	>
>;

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
struct do_convert
{
	static
	sge::charconv::string_type<
		DestEncoding
	>
	execute(
		sge::charconv::string_type<
			SourceEncoding
		> const &_source
	)
	{
		converter_impl<
			SourceEncoding
		>
		source_to_utf8;

		converter_impl<
			DestEncoding
		>
		utf8_to_dest;

		return
			utf8_to_dest.from_bytes(
				source_to_utf8.to_bytes(
					_source
				)
			);
	}
};

template<
	sge::charconv::encoding DestEncoding
>
struct do_convert<
	DestEncoding,
	sge::charconv::encoding::utf8
>
{
	static
	sge::charconv::string_type<
		DestEncoding
	>
	execute(
		sge::charconv::string_type<
			sge::charconv::encoding::utf8
		> const &_source
	)
	{
		converter_impl<
			DestEncoding
		>
		utf8_to_dest;

		return
			utf8_to_dest.from_bytes(
				_source
			);
	}
};

template<
	sge::charconv::encoding SourceEncoding
>
struct do_convert<
	sge::charconv::encoding::utf8,
	SourceEncoding
>
{
	static
	sge::charconv::string_type<
		sge::charconv::encoding::utf8
	>
	execute(
		sge::charconv::string_type<
			SourceEncoding
		> const &_source
	)
	{
		converter_impl<
			SourceEncoding
		>
		source_to_utf8;

		return
			source_to_utf8.to_bytes(
				_source
			);
	}
};

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
typename
std::enable_if<
	DestEncoding
	==
	SourceEncoding,
	sge::charconv::string_type<
		DestEncoding
	>
>::type
convert_or_id(
	sge::charconv::string_type<
		SourceEncoding
	> const &_source
)
{
	return
		_source;
}

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
typename
std::enable_if<
	DestEncoding
	!=
	SourceEncoding,
	sge::charconv::string_type<
		DestEncoding
	>
>::type
convert_or_id(
	sge::charconv::string_type<
		SourceEncoding
	> const &_source
)
{
	return
		do_convert<
			DestEncoding,
			SourceEncoding
		>::execute(
			_source
		);
}

}

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
sge::charconv::string_type<
	DestEncoding
>
sge::charconv::convert(
	sge::charconv::string_type<
		SourceEncoding
	> const &_source
)
try
{
	return
		convert_or_id<
			DestEncoding,
			SourceEncoding
		>(
			_source
		);
}
catch(
	std::range_error const &
)
{
	throw
		sge::charconv::conversion_failed{};
}

#define SGE_CHARCONV_INSTANTIATE_ENCODING(\
	r,\
	param\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::charconv::string_type< \
	BOOST_PP_SEQ_ELEM(0, param) \
> \
sge::charconv::convert<\
	BOOST_PP_SEQ_ELEM(0, param),\
	BOOST_PP_SEQ_ELEM(1, param)\
>( \
	sge::charconv::string_type< \
		BOOST_PP_SEQ_ELEM(1, param) \
	> const & \
);

#define SGE_CHARCONV_ENCODINGS \
(sge::charconv::encoding::utf8)\
(sge::charconv::encoding::utf16)\
(sge::charconv::encoding::utf32)\
(sge::charconv::encoding::wchar)

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
	SGE_CHARCONV_INSTANTIATE_ENCODING,
	(SGE_CHARCONV_ENCODINGS)(SGE_CHARCONV_ENCODINGS)
)
