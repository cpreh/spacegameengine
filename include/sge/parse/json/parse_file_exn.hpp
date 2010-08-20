#ifndef SGE_PARSE_JSON_PARSE_FILE_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_PARSE_FILE_EXN_HPP_INCLUDED

#include <sge/symbol.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace parse
{
namespace json
{
SGE_SYMBOL object const
parse_file_exn(
	fcppt::filesystem::path const &);
}
}
}

#endif
