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


#include <sge/charconv/const_raw_pointer.hpp>
#include <sge/charconv/conversion_failed.hpp>
#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/converter.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/raw_pointer.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/system.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


template<
	sge::charconv::encoding::type DestEncoding,
	sge::charconv::encoding::type SourceEncoding
>
typename sge::charconv::string_type<
	DestEncoding
>::type
sge::charconv::convert(
	sge::charconv::system &_system,
	typename charconv::string_type<
		SourceEncoding
	>::type const &_source
)
{
	typedef typename charconv::string_type<
		SourceEncoding
	>::type source_type;

	typedef typename charconv::string_type<
		DestEncoding
	>::type dest_type;

	if(
		_source.empty()
	)
		return dest_type();

	sge::charconv::converter_ptr const converter(
		_system.create_converter(
			charconv::source_encoding(
				SourceEncoding
			),
			charconv::dest_encoding(
				DestEncoding
			)
		)
	);

	typedef fcppt::container::raw_vector<
		typename source_type::value_type
	> source_buffer_type;

	source_buffer_type source_buffer(
		_source.begin(),
		_source.end()
	);

	typedef fcppt::container::raw_vector<
		typename dest_type::value_type
	> dest_buffer_type;

	// some guess
	dest_buffer_type dest_buffer(
		_source.size()
	);

	charconv::input_range source_range(
		reinterpret_cast<
			charconv::const_raw_pointer
		>(
			source_buffer.data()
		),
		reinterpret_cast<
			charconv::const_raw_pointer
		>(
			source_buffer.data_end()
		)
	);

	charconv::output_range dest_range(
		reinterpret_cast<
			charconv::raw_pointer
		>(
			dest_buffer.data()
		),
		reinterpret_cast<
			charconv::raw_pointer
		>(
			dest_buffer.data_end()
		)
	);

	for(;;)
	{
		charconv::conversion_status::type const status(
			converter->convert(
				source_range,
				dest_range
			)
		);

		typedef typename dest_buffer_type::size_type dest_size_type;

		dest_size_type const elements_converted(
			dest_buffer.size()
			-
			static_cast<
				dest_size_type
			>(
				dest_range.size()
			)
			/ sizeof(typename dest_type::value_type)
		);

		switch(
			status
		)
		{
		case charconv::conversion_status::invalid_input:
		case charconv::conversion_status::incomplete_input:
			throw charconv::conversion_failed();
		case charconv::conversion_status::ok:
			return
				dest_type(
					dest_buffer.data(),
					dest_buffer.data()
					+ elements_converted
				);
		case charconv::conversion_status::output_too_small:
			dest_buffer.resize(
				dest_buffer.size() * 2
			);

			dest_range =
				charconv::output_range(
					reinterpret_cast<
						charconv::raw_pointer
					>(
						dest_buffer.data()
						+ elements_converted
					),
					reinterpret_cast<
						charconv::raw_pointer
					>(
						dest_buffer.data_end()
					)
				);
		}
	}
}

#define SGE_CHARCONV_INSTANTIATE_ENCODING(\
	r,\
	param\
)\
template \
FCPPT_EXPORT_SYMBOL \
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
