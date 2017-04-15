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


#include <sge/config/getenv.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/src/core/include_windows.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from_opt.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#else
#include <fcppt/from_std_string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>
#endif


fcppt::optional_string
sge::config::getenv(
	fcppt::string const &_name
)
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	typedef
	fcppt::container::buffer::object<
		fcppt::char_type
	>
	buffer_type;
	
	return
		fcppt::optional::map(
			fcppt::container::buffer::read_from_opt<
				fcppt::char_type
			>(
				// An environment variable cannot be longer than 32767 characters
				32767u,
				[
					&_name
				](
					buffer_type::pointer const _data,
					buffer_type::size_type const _size
				)
				{
					DWORD const ret(
						::GetEnvironmentVariable(
							_name.c_str(),
							_data,
							fcppt::cast::size<
								DWORD
							>(
								_size
							)
						)
					);

					return
						fcppt::optional::make_if(
							ret
							!=
							0u,
							[
								ret
							]{
								return
									fcppt::cast::size<
										buffer_type::size_type
									>(
										ret
									);
							}
						);
				}
			),
			[](
				fcppt::container::buffer::object<
					fcppt::char_type
				> &&_buffer
			)
			{
				return
					fcppt::string{
						_buffer.read_data()
					};
			}
		);
#else
	char const *const ret(
		::std::getenv(
			fcppt::to_std_string(
				_name
			).c_str()
		)
	);

	return
		ret
		!=
		nullptr
		?
			fcppt::optional_string(
				fcppt::from_std_string(
					ret
				)
			)
		:
			fcppt::optional_string();
#endif
}
