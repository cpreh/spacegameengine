/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/charconv/conversion_failed.hpp>
#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/convert_raw.hpp>
#include <sge/charconv/converter.hpp>
#include <sge/charconv/converter_unique_ptr.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/raw_vector.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/system.hpp>


sge::charconv::raw_vector const
sge::charconv::convert_raw(
	sge::charconv::system &_system,
	sge::charconv::source_encoding const _source,
	sge::charconv::dest_encoding const _dest,
	sge::charconv::input_range const &_input
)
{
	if(
		_input.size()
		==
		0
	)
		return sge::charconv::raw_vector();

	sge::charconv::converter_unique_ptr converter(
		_system.create_converter(
			_source,
			_dest
		)
	);

	// some guess
	sge::charconv::raw_vector dest_buffer(
		static_cast<
			sge::charconv::raw_vector::size_type
		>(
			_input.size()
		)
	);

	sge::charconv::input_range source_range(
		_input
	);

	sge::charconv::output_range dest_range(
		dest_buffer.data(),
		dest_buffer.data_end()
	);

	for(
		;;
	)
	{
		sge::charconv::conversion_status const status(
			converter->convert(
				source_range,
				dest_range
			)
		);

		typedef sge::charconv::raw_vector::size_type dest_size_type;

		dest_size_type const elements_converted(
			dest_buffer.size()
			-
			static_cast<
				dest_size_type
			>(
				dest_range.size()
			)
		);

		switch(
			status
		)
		{
		case sge::charconv::conversion_status::invalid_input:
		case sge::charconv::conversion_status::incomplete_input:
			throw sge::charconv::conversion_failed();
		case sge::charconv::conversion_status::ok:
			dest_buffer.resize_uninitialized(
				elements_converted
			);

			return
				dest_buffer;
		case sge::charconv::conversion_status::output_too_small:
			dest_buffer.resize(
				dest_buffer.size() * 2
			);

			dest_range =
				sge::charconv::output_range(
					dest_buffer.data()
					+ elements_converted,
					dest_buffer.data_end()
				);
		}
	}
}
