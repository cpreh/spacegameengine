//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_FCPPT_STRING_TO_UTF8_FILE_HPP_INCLUDED
#define SGE_CHARCONV_FCPPT_STRING_TO_UTF8_FILE_HPP_INCLUDED

#include <sge/charconv/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace charconv
{

[[nodiscard]]
SGE_CHARCONV_DETAIL_SYMBOL
bool
fcppt_string_to_utf8_file(
	fcppt::string const &,
	std::filesystem::path const &
);

}
}

#endif
