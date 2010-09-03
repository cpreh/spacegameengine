#ifndef SGE_PARSE_PARSE_FILE_EXN_HPP_INCLUDED
#define SGE_PARSE_PARSE_FILE_EXN_HPP_INCLUDED

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
	fcppt::filesystem::path const &_path
)
{
	Result result;

	if( 
		!parse::parse_file(
			_path,
			result
		)
	)
		throw sge::parse::exception(
			FCPPT_TEXT("Unable to parse file \"")
			+
			_path.string()
		);

	return result;
}

}
}

#endif
