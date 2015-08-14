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


#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters_fwd.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/plugin/traits.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/src/media/muxer_impl.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>



sge::image2d::multi_system::multi_system(
	sge::image2d::multi_system_parameters const &_params
)
:
	muxer_(
		_params
	)
{
}

sge::image2d::multi_system::~multi_system()
{
}

sge::image2d::optional_file_unique_ptr
sge::image2d::multi_system::load(
	boost::filesystem::path const &_path
)
{
	return
		muxer_.mux_path(
			_path,
			muxer::load_function{
				std::bind(
					&sge::image2d::system::load,
					std::placeholders::_1,
					_path
				)
			}
		);
}

sge::image2d::optional_file_unique_ptr
sge::image2d::multi_system::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension,
			muxer::load_function{
				std::bind(
					&sge::image2d::system::load_raw,
					std::placeholders::_1,
					_range,
					_extension
				)
			}
		);
}

sge::image2d::optional_file_unique_ptr
sge::image2d::multi_system::load_stream(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension,
			muxer::load_function{
				std::bind(
					&sge::image2d::system::load_stream,
					std::placeholders::_1,
					std::ref(
						_stream
					),
					_extension
				)
			}
		);
}

sge::image2d::optional_file_unique_ptr
sge::image2d::multi_system::create(
	sge::image2d::view::const_object const &_object,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension,
			muxer::load_function{
				std::bind(
					&sge::image2d::system::create,
					std::placeholders::_1,
					std::cref(
						_object
					),
					_extension
				)
			}
		);
}

sge::media::extension_set
sge::image2d::multi_system::extensions() const
{
	return
		muxer_.extensions();
}
