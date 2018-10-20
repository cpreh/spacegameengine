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


#include <sge/image2d/file.hpp>
#include <sge/image2d/load_stream_result.hpp>
#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/plugin/collection.hpp>
#include <sge/image2d/plugin/context.hpp>
#include <sge/image2d/plugin/iterator.hpp>
#include <sge/image2d/plugin/object.hpp>
#include <sge/image2d/plugin/traits.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/media/impl/muxer_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/bind.hpp>


sge::image2d::multi_system::multi_system(
	sge::image2d::multi_system_parameters const &_params
)
:
	sge::image2d::system(),
	muxer_(
		_params
	)
{
}

sge::image2d::multi_system::~multi_system()
{
}

sge::image2d::load_stream_result
sge::image2d::multi_system::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		muxer_.mux_stream(
			std::move(
				_stream
			),
			_extension,
			_name
		);
}

sge::image2d::optional_file_unique_ptr
sge::image2d::multi_system::create(
	sge::image2d::view::const_object const &_view,
	sge::media::extension const &_extension
)
{
	return
		fcppt::optional::bind(
			muxer_.mux_extension(
				_extension
			),
			[
				&_view,
				&_extension
			](
				fcppt::reference<
					sge::image2d::system
				> const _system
			)
			{
				return
					_system.get().create(
						_view,
						_extension
					);
			}
		);
}

sge::media::extension_set
sge::image2d::multi_system::extensions() const
{
	return
		muxer_.extensions();
}
