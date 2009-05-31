#include <sge/filesystem/create_directory.hpp>
#include <boost/filesystem/operations.hpp>

bool sge::filesystem::create_directory(
	path const &p)
{
	return boost::filesystem::create_directory(
		p);
}
