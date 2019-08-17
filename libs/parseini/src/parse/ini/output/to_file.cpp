//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/impl/output/to_file.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_file.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


bool
sge::parse::ini::output::to_file(
	std::filesystem::path const &_path,
	sge::parse::ini::start const &_data
)
{
	return
		sge::parse::impl::output::to_file<
			char
		>(
			&sge::parse::ini::output::to_stream,
			_path,
			_data
		);
}
