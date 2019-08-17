//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_OUTPUT_TO_FILE_HPP_INCLUDED
#define SGE_PARSE_INI_OUTPUT_TO_FILE_HPP_INCLUDED

#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{
namespace output
{

[[nodiscard]]
SGE_PARSE_INI_DETAIL_SYMBOL
bool
to_file(
	std::filesystem::path const &,
	sge::parse::ini::start const &
);

}
}
}
}

#endif
