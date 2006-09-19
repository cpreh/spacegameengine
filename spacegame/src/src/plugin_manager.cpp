#include "../plugin_manager.hpp"
#include "../library.hpp"
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

namespace
{
	typedef void (*version_function)(sge::plugin_info*);
	inline version_function get_version_function(sge::library& lib)
	{
		return lib.load_function<version_function>("plugin_version_info");
	}

	const char* const plugin_path = PLUGIN_PATH;
	const char* const plugin_extension = ".so";
}

sge::plugin_manager::plugin_manager()
	: mypath(plugin_path)
{
	std::cout << "Scanning for plugins in " << plugin_path << " ...\n";
	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(mypath); it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it))
			continue;
		if(boost::filesystem::extension(*it)!=plugin_extension)
			continue;
		library lib(it->string());
		version_function vf = get_version_function(lib);
		plugin_infos.push_back(plugin_info());
		plugin_info& i = plugin_infos.back();
		vf(&i);
		i.path = it->string();
		std::cout << "Plugin found: " << i.name << " | " << i.description << " (mask=" << i.type << ")\n";
	}	
}

void sge::plugin_manager::get_plugin_info(const plugin_type mask, plugin_info_array& v)
{
	for(plugin_info_array::const_iterator it = plugin_infos.begin(); it != plugin_infos.end(); ++it)
		if(it->type & mask)
			v.push_back(*it);
}

void sge::plugin_manager::load_plugin(const plugin_type mask, const unsigned number)
{
	plugin_info_array v;
	get_plugin_info(mask,v);
	try
	{
		const plugin_info_array::const_reference i = v.at(number);
		load_plugin(i.path);
	}
	catch(const std::exception&)
	{
		std::cerr << "No plugin found with mask = " << mask << " and number = " << number << "!\n";
		throw;
	}
}

void sge::plugin_manager::load_plugin(const std::string& file)
{
	library_ptr l(new library(file));
	version_function vf = get_version_function(*l);
	plugin_info i;
	vf(&i);
	plugin p(l,i.type);
	loaded_plugins.push_back(p);
	std::cout << "Plugin: " << file << " loaded!\n";
}
