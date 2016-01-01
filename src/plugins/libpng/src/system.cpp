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
#include <sge/image2d/load_stream_result.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/libpng/extension.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/file_rep_from_stream.hpp>
#include <sge/libpng/file_rep_from_view.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/system.hpp>
#include <sge/media/check_extension.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::system::system()
:
	sge::image2d::system()
{
}

sge::libpng::system::~system()
{
}

sge::image2d::load_stream_result
sge::libpng::system::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		sge::media::check_extension(
			sge::libpng::extension(),
			_extension
		)
		&&
		sge::libpng::is_png(
			*_stream
		)
		?
			fcppt::optional::maybe(
				sge::libpng::file_rep_from_stream(
					*_stream,
					_name
				),
				[
					&_stream
				]{
					return
						sge::image2d::load_stream_result{
							std::move(
								_stream
							)
						};
				},
				[](
					sge::libpng::file_rep &&_rep
				)
				{
					return
						sge::image2d::load_stream_result{
							fcppt::unique_ptr_to_base<
								sge::image2d::file
							>(
								fcppt::make_unique_ptr<
									sge::libpng::file
								>(
									std::move(
										_rep
									)
								)
							)
						};
				}
			)
		:
			sge::image2d::load_stream_result{
				std::move(
					_stream
				)
			}
		;
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::create(
	sge::image2d::view::const_object const &_view,
	sge::media::extension const &_extension
)
{
	return
		_extension
		==
		sge::libpng::extension()
		?
			fcppt::optional::map(
				sge::libpng::file_rep_from_view(
					_view
				),
				[](
					sge::libpng::file_rep &&_rep
				)
				{
					return
						fcppt::unique_ptr_to_base<
							sge::image2d::file
						>(
							fcppt::make_unique_ptr<
								file
							>(
								std::move(
									_rep
								)
							)
						);
				}
			)
		:
			sge::image2d::optional_file_unique_ptr()
		;
}

sge::media::extension_set
sge::libpng::system::extensions() const
{
	return
		sge::media::extension_set{
			sge::libpng::extension()
		};
}
