#ifndef SGE_PARSE_FILE_EXN_HPP_INCLUDED
#define SGE_PARSE_FILE_EXN_HPP_INCLUDED

#include "parse_file.hpp"
#include <sge/parse/exception.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/text.hpp>

namespace sge
{
namespace parse
{
template<
	typename Result
>
Result const
parse_file_exn(
	fcppt::filesystem::path const &path)
{
	fcppt::io::ifstream ifs(
		path,
		std::ios_base::binary
	);

	Result result;

	if ( 
		!parse_file(
			path,
			result
		))
	throw exception(
		FCPPT_TEXT("Unable to parse file \"")+path.string()+FCPPT_TEXT(""));

	return result;
}
}
}

#endif
