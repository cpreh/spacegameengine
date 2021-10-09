//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CHARCONV_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED
#define SGE_CHARCONV_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED

#include <sge/charconv/detail/symbol.hpp>
#include <fcppt/optional_string_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::charconv
{

SGE_CHARCONV_DETAIL_SYMBOL
fcppt::optional_string utf8_file_to_fcppt_string(std::filesystem::path const &);

}

#endif
