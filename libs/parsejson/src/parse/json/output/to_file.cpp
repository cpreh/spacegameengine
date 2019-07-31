//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/impl/output/to_file.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


bool
sge::parse::json::output::to_file(
	boost::filesystem::path const &_path,
	sge::parse::json::start const &_data
)
{
	return
		sge::parse::impl::output::to_file<
			char
		>(
			&sge::parse::json::output::to_stream,
			_path,
			_data
		);
}
