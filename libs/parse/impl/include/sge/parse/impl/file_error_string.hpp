//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_IMPL_FILE_ERROR_STRING_HPP_INCLUDED
#define SGE_PARSE_IMPL_FILE_ERROR_STRING_HPP_INCLUDED

#include <sge/parse/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/parse/error_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace impl
{

SGE_PARSE_DETAIL_SYMBOL
fcppt::string
file_error_string(
	std::filesystem::path const &,
	fcppt::parse::error<
		char
	> &&
);

SGE_PARSE_DETAIL_SYMBOL
fcppt::string
file_error_string(
	std::filesystem::path const &,
	fcppt::parse::error<
		wchar_t
	> &&
);

}
}
}

#endif
