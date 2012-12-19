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


#include <sge/charconv/const_raw_pointer.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/convert_raw.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/raw_vector.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/src/export_function_instantiation.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/data.hpp>
#include <fcppt/container/data_end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>


template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
typename sge::charconv::string_type<
	DestEncoding
>::type
sge::charconv::convert(
	sge::charconv::system &_system,
	typename sge::charconv::string_type<
		SourceEncoding
	>::type const &_source
)
{
	sge::charconv::raw_vector const raw_result(
		sge::charconv::convert_raw(
			_system,
			sge::charconv::source_encoding(
				SourceEncoding
			),
			sge::charconv::dest_encoding(
				DestEncoding
			),
			// A string must be contiguous in C++11 and most
			// implementations do it that anyway
			sge::charconv::input_range(
				reinterpret_cast<
					sge::charconv::const_raw_pointer
				>(
					fcppt::container::data(
						_source
					)
				),
				reinterpret_cast<
					sge::charconv::const_raw_pointer
				>(
					fcppt::container::data_end(
						_source
					)
				)
			)
		)
	);

	typedef typename sge::charconv::string_type<
		DestEncoding
	>::type dest_type;

	// Copy the result over to avoid strict-aliasing problems
	dest_type dest;

	FCPPT_ASSERT_ERROR(
		raw_result.size()
		%
		sizeof(typename dest_type::value_type)
		==
		0u
	);

	dest.resize(
		raw_result.size()
		/
		sizeof(typename dest_type::value_type)
	);

	std::memcpy(
		fcppt::container::data(
			dest
		),
		raw_result.data(),
		raw_result.size()
	);

	return
		dest;
}

#define SGE_CHARCONV_INSTANTIATE_ENCODING(\
	r,\
	param\
)\
template \
SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::charconv::string_type< \
	BOOST_PP_SEQ_ELEM(0, param) \
>::type \
sge::charconv::convert<\
	BOOST_PP_SEQ_ELEM(0, param),\
	BOOST_PP_SEQ_ELEM(1, param)\
>( \
	sge::charconv::system &, \
	sge::charconv::string_type< \
		BOOST_PP_SEQ_ELEM(1, param) \
	>::type const & \
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
