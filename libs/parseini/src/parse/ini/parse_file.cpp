//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/impl/parse_file.hpp>
#include <sge/parse/ini/file_result.hpp>
#include <sge/parse/ini/grammar.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::parse::ini::file_result
sge::parse::ini::parse_file(
	boost::filesystem::path const &_path
)
{
	return
		sge::parse::impl::parse_file(
			_path,
			sge::parse::ini::grammar{}
		);
}
