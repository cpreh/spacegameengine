#include "../file.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

sge::find_file_ret sge::find_file(const std::string& path, const std::string& filename, const bool recursive, const bool ignore_extension)
{
	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(path); it != end; ++it)
		if(boost::filesystem::is_directory(*it))
		{
			if(!recursive)
				continue;
			find_file_ret r = find_file(it->string(),filename,recursive,ignore_extension);
			if(r.second)
				return r;
		}
		else
		{
			if(!ignore_extension && it->leaf() == filename)
				return std::make_pair(it->string(),true);
			else if(ignore_extension && boost::filesystem::basename(*it) == filename)
				return std::make_pair(it->string(),true);
		}
	return std::make_pair(std::string(),false);
}
