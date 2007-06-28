/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include "../plugin_manager.hpp"

typedef void (*version_function)(sge::plugin_info*);

const char* const plugin_path = PLUGIN_PATH;
const char* const plugin_extension =
#ifdef SGE_LINUX_PLATFORM
	".so"
#elif SGE_WINDOWS_PLATFORM
	".dll"
#endif
	;

sge::plugin_manager::plugin_manager()
{
	boost::filesystem::path plugin_dir(plugin_path);

	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(plugin_dir); it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it) || boost::filesystem::extension(*it)!=plugin_extension)
			continue;

		plugins.push_back(plugin_context_base(it->string()));
	}

	for(plugin_array::iterator it = plugins.begin(); it != plugins.end(); ++it)
		for(unsigned i = 1; i < PT_Last_Guard; i <<= 1)
		{
			const unsigned type = it->type();
			if(type & i)
				categories[static_cast<plugin_type>(i)].push_back(&*it);
		}
}

sge::plugin_manager::plugin_context_base::plugin_context_base(const string& _path)
: _path(_path)
{
	library lib(path());
	version_function vf = lib.load_function<version_function>("plugin_version_info");
	plugin_info info;
	vf(&info);
	_name = info.name;
	_description = info.description;
	_version = info.plugin_version;
	_type = info.type;
}

const sge::string& sge::plugin_manager::plugin_context_base::name() const
{
	return _name;
}

const sge::string& sge::plugin_manager::plugin_context_base::description() const
{
	return _description;
}

unsigned sge::plugin_manager::plugin_context_base::version() const
{
	return _version;
}

sge::plugin_type sge::plugin_manager::plugin_context_base::type() const
{
	return _type;
}

const sge::string& sge::plugin_manager::plugin_context_base::path() const
{
	return _path;
}
