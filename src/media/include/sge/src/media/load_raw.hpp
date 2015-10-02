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


#ifndef SGE_SRC_MEDIA_LOAD_RAW_HPP_INCLUDED
#define SGE_SRC_MEDIA_LOAD_RAW_HPP_INCLUDED

#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/io/raw_container_source.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename Result,
	typename System
>
fcppt::optional<
	Result
>
load_raw(
	System &_system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	typedef
	boost::iostreams::stream<
		fcppt::io::raw_container_source<
			fcppt::container::raw_vector<
				char
			>
		>
	>
	stream_type;

	return
		fcppt::variant::to_optional<
			Result
		>(
			_system.load_stream(
				fcppt::unique_ptr_to_base<
					std::istream
				>(
					fcppt::make_unique_ptr<
						stream_type
					>(
						fcppt::cast::to_char_ptr<
							boost::iostreams::array_source::char_type const *
						>(
							_range.begin()
						),
						fcppt::cast::to_char_ptr<
							boost::iostreams::array_source::char_type const *
						>(
							_range.end()
						)
					)
				),
				_extension,
				sge::media::optional_name()
			)
		);
}

}
}

#endif
