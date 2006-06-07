#ifndef SGE_FILE_HPP_INCLUDED
#define SGE_FILE_HPP_INCLUDED

#include <string>
#include <utility>

namespace sge
{
	typedef std::pair<std::string,bool> find_file_ret;
	find_file_ret find_file(const std::string& path, const std::string& filename, bool recursive = true, bool ignore_extension = true);
}

#endif
