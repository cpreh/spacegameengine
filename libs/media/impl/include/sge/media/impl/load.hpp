//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_LOAD_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_HPP_INCLUDED

#include <sge/media/file_exception.hpp>
#include <sge/media/name.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/path_to_extension.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
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
	fcppt::reference<
		System
	> const _system,
	std::filesystem::path const &_path
)
{
	auto file_stream(
		fcppt::make_unique_ptr<
			std::ifstream
		>(
			_path,
			std::ios_base::binary
		)
	);

	if(
		!file_stream->is_open()
	)
	{
		throw
			Exception{
				FCPPT_TEXT("Couldn't open ")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
			};
	}

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
				_system.get().load_stream(
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
