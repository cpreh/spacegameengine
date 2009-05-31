#ifndef SGE_FILESYSTEM_CREATE_DIRECTORY_HPP_INCLUDED
#define SGE_FILESYSTEM_CREATE_DIRECTORY_HPP_INCLUDED

#include <sge/export.hpp>
#include <sge/filesystem/path.hpp>

namespace sge
{
namespace filesystem
{
SGE_SYMBOL bool create_directory(
	path const &);
}
}

#endif
