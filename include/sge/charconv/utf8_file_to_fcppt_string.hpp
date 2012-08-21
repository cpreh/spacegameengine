#ifndef SGE_CHARCONV_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED
#define SGE_CHARCONV_UTF8_FILE_TO_FCPPT_STRING_HPP_INCLUDED

#include <sge/charconv/symbol.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace charconv
{
SGE_CHARCONV_SYMBOL
fcppt::string const
utf8_file_to_fcppt_string(
	sge::charconv::system &,
	boost::filesystem::path const &);
}
}

#endif
