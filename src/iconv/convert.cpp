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


#include <sge/iconv/convert.hpp>
#include <sge/iconv/const_raw_pointer.hpp>
#include <sge/iconv/conversion_failed.hpp>
#include <sge/iconv/encoding_to_string.hpp>
#include <sge/iconv/object.hpp>
#include <sge/iconv/raw_pointer.hpp>
#include <sge/iconv/size_type.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <iterator>

template<
	sge::iconv::encoding::type DestEncoding,
	sge::iconv::encoding::type SourceEncoding
>
typename sge::iconv::string_type<
	DestEncoding
>::type
sge::iconv::convert(
	typename iconv::string_type<
		SourceEncoding
	>::type const &_source
)
{
	typedef typename iconv::string_type<
		SourceEncoding
	>::type source_type;

	typedef typename iconv::string_type<
		DestEncoding
	>::type dest_type;

	if(
		_source.empty()
	)
		return dest_type();

	iconv::object obj(
		iconv::encoding_to_string(
			SourceEncoding
		),
		iconv::encoding_to_string(
			DestEncoding
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

	iconv::const_raw_pointer source_ptr(
		_source.data()
	);

	iconv::size_type in_bytes_left(
		_source.size()
		* sizeof(source_type::value_type)
	);

	iconv::raw_pointer dest_ptr(
		reinterpret_cast<
			iconv::raw_pointer
		>(
			dest_buffer.data()
		)
	);

	for(;;)
	{
		iconv::size_type out_bytes_left(
			std::distance(
				dest_ptr,
				dest_buffer.data_end()
			)
			* sizeof(dest_type::value_type)
		);

		iconv::conversion_status::type const status(
			obj.convert(
				source_ptr,
				in_bytes_left,
				dest_ptr,
				out_bytes_left
			)
		);

		iconv::size_type const elements_converted(
			dest_buffer.size()
			- out_bytes_left
			/ sizeof(dest_type::value_type)
		);

		switch(
			status
		)
		{
		case iconv::conversion_status::invalid_sequence:
		case iconv::conversion_status::incomplete_input:
			throw iconv::conversion_failed();	
		case iconv::conversion_status::ok:
			return
				dest_type(
					dest_buffer.data(),
					dest_buffer.data()
					+ elements_converted
				);
		case iconv::conversion_status::output_too_small:
			dest_buffer.resize(
				dest_buffer.size() * 2
			);

			dest_ptr =
				dest_buffer.data()
				+ elements_converted;
		}
	}
}
