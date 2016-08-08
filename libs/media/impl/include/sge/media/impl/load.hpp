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


#ifndef SGE_MEDIA_IMPL_LOAD_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_HPP_INCLUDED

#include <sge/media/file_exception.hpp>
#include <sge/media/name.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/path_to_extension.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <ios>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{
namespace impl
{

template<
	typename Result,
	typename Exception,
	typename System
>
fcppt::optional::object<
	Result
>
load(
	System &_system,
	boost::filesystem::path const &_path
)
{
	auto file_stream(
		fcppt::make_unique_ptr<
			boost::filesystem::ifstream
		>(
			_path,
			std::ios_base::binary
		)
	);

	if(
		!file_stream->is_open()
	)
		throw
			Exception{
				FCPPT_TEXT("Couldn't open ")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
			};

	sge::media::optional_name const cur_name{
		sge::media::name{
			fcppt::filesystem::path_to_string(
				_path
			)
		}
	};

	try
	{
		return
			fcppt::variant::to_optional<
				Result
			>(
				_system.load_stream(
					fcppt::unique_ptr_to_base<
						std::istream
					>(
						std::move(
							file_stream
						)
					),
					sge::media::path_to_extension(
						_path
					),
					cur_name
				)
			);
	}
	catch(
		fcppt::exception const &_error
	)
	{
		throw
			sge::media::file_exception<
				Exception
			>(
				cur_name,
				_error.string()
			);
	}
}

}
}
}

#endif
