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


#include <sge/audio/file.hpp>
#include <sge/audio/load_stream_result.hpp>
#include <sge/audio/loader.hpp>
#include <sge/media/check_extension.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/wave/file.hpp>
#include <sge/wave/info_fwd.hpp>
#include <sge/wave/loader.hpp>
#include <sge/wave/read_info.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension const extension(
	FCPPT_TEXT("wav")
);

}

sge::wave::loader::loader()
:
	sge::audio::loader()
{
}

sge::wave::loader::~loader()
{
}

sge::audio::load_stream_result
sge::wave::loader::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		sge::media::check_extension(
			extension,
			_extension
		)
		?
			fcppt::optional::maybe(
				sge::wave::read_info(
					*_stream,
					_name
				),
				[
					&_stream
				]{
					return
						sge::audio::load_stream_result{
							std::move(
								_stream
							)
						};
				},
				[
					&_stream,
					&_name
				](
					sge::wave::info const &_info
				)
				{
					return
						sge::audio::load_stream_result{
							fcppt::unique_ptr_to_base<
								sge::audio::file
							>(
								fcppt::make_unique_ptr<
									sge::wave::file
								>(
									std::move(
										_stream
									),
									_info,
									_name
								)
							)
						};
				}
			)
		:
			sge::audio::load_stream_result{
				std::move(
					_stream
				)
			}
		;
}

sge::media::extension_set
sge::wave::loader::extensions() const
{
	return
		sge::media::extension_set{
			extension
		};
}
