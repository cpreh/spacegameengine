// Fuck man, why do I have to include that crap here?
#include <istream>
#include "../parse_file_exn.hpp"
#include <sge/parse/json/parse_file.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <fcppt/filesystem/path.hpp>

sge::parse::json::object const
sge::parse::json::parse_file_exn(
	fcppt::filesystem::path const &p)
{
	return 
		parse::parse_file_exn<object>(
			p);
}
