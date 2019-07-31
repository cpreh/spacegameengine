//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_PARSE_FILE_HPP_INCLUDED
#define SGE_PARSE_INI_PARSE_FILE_HPP_INCLUDED

#include <sge/parse/ini/file_result.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

SGE_PARSE_INI_DETAIL_SYMBOL
sge::parse::ini::file_result
parse_file(
	boost::filesystem::path const &
);

}
}
}

#endif
