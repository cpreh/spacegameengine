//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/impl/parse_file_exn.hpp>
#include <sge/parse/json/grammar.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::parse::json::start
sge::parse::json::parse_file_exn(
	boost::filesystem::path const &_path
)
{
	return
		sge::parse::impl::parse_file_exn(
			_path,
			sge::parse::json::grammar{}
		);
}
