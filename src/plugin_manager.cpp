/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/config.h>
#include <sge/plugin_manager.hpp>
#include <sge/iconv.hpp>
#include <sge/path.hpp>
#include <sge/text.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>

typedef void (*version_function)(sge::plugin_info*);

const char* const plugin_path =
#ifndef _MSC_VER
  PLUGIN_PATH
#else
PLUGIN_PATH "/" CMAKE_INTDIR
#endif
  ;
const sge::string::const_pointer plugin_extension =
#ifdef SGE_POSIX_PLATFORM
	SGE_TEXT(".so")
#elif SGE_WINDOWS_PLATFORM
	SGE_TEXT(".dll")
#else
#error "Don't know which plugin extension to use!"
#endif
	;

sge::plugin_manager::plugin_manager()
{
	const directory_iterator end;
	for(directory_iterator it(iconv(plugin_path)); it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it) || boost::filesystem::extension(*it)!=plugin_extension)
			continue;

		try {
			plugins.push_back(plugin_context_base(*it));
		} catch(const library::load_function_exception &e) {
			// ignore info loading error - it's just a DLL, not a plugin...
			// nothing to worry about (and especially nothing that justifies
			// aborting the program ...)
			if (e.func != "plugin_version_info") throw;
		}
	}

	for(plugin_array::iterator it = plugins.begin(); it != plugins.end(); ++it)
		for(unsigned i = 1; i < plugin_type::_last_guard; i <<= 1)
		{
			const unsigned type = it->type();
			if(type & i)
				categories[static_cast<plugin_type::type>(i)].push_back(&*it);
		}
}

sge::plugin_manager::plugin_context_base::plugin_context_base(const path& path_)
: path_(path_)
{
	library lib(get_path());
	version_function vf = lib.load_function<version_function>("plugin_version_info");
	plugin_info info;
	vf(&info);
	name_ = info.name;
	description_ = info.description;
	version_ = info.plugin_version;
	type_ = info.type;
}

const sge::string& sge::plugin_manager::plugin_context_base::name() const
{
	return name_;
}

const sge::string& sge::plugin_manager::plugin_context_base::description() const
{
	return description_;
}

unsigned sge::plugin_manager::plugin_context_base::version() const
{
	return version_;
}

sge::plugin_type::type sge::plugin_manager::plugin_context_base::type() const
{
	return type_;
}

const sge::path& sge::plugin_manager::plugin_context_base::get_path() const
{
	return path_;
}
