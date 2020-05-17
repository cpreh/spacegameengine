//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/app_path.hpp>
#include <sge/config/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/core/impl/include_windows.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/container/raw_vector/object_impl.hpp>
#endif


std::filesystem::path
sge::config::app_path()
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	using
	buffer_type
	=
	fcppt::container::raw_vector::object<
		fcppt::char_type
	>;

	buffer_type const buf{
		fcppt::container::buffer::to_raw_vector(
			fcppt::container::buffer::read_from<
				fcppt::container::buffer::object<
					fcppt::char_type
				>
			>(
				32768u,
				[](
					buffer_type::pointer const _data,
					buffer_type::size_type const _size
				)
				{
					DWORD const count{
						::GetModuleFileName(
							NULL,
							_data,
							fcppt::cast::size<
								DWORD
							>(
								_size
							)
						)
					};

					if(
						count
						==
						0u
					)
					{
						throw
							sge::config::exception{
								FCPPT_TEXT("GetModuleFileName() failed!")
							};
					}

					return
						count;
				}
			)
		)
	};

	return
		std::filesystem::path(
			fcppt::string{
				buf.data(),
				buf.data_end()
			}
		).parent_path();
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	std::filesystem::path const self(
		"/proc/self/exe"
	);

	if(
		!std::filesystem::exists(
			self
		)
	)
	{
		throw
			sge::config::exception{
				FCPPT_TEXT("/prof/self/exe does not exist")
			};
	}

	return
		std::filesystem::read_symlink(
			self
		).parent_path();
#else
#error "Implement me!"
#endif
}
