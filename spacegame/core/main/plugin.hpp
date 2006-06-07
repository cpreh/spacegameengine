#ifndef SGE_PLUGIN_HPP_INCLUDED
#define SGE_PLUGIN_HPP_INCLUDED

#include <string>

namespace sge
{
	enum plugin_type {
		PT_Nothing          = 0,
		PT_Renderer         = 1,
		PT_Input            = 1 << 1,
		PT_ImageLoader      = 1 << 2,
		PT_Audio            = 1 << 3,
		PT_Font             = 1 << 4,
		PT_Last_Guard       = 1 << 5
	};

	struct plugin_info {
		plugin_info()
			: name(0), description(0), plugin_version(0), 
			  min_core_version(0), type(PT_Nothing) {}
		const char*  name;
		const char*  description;
		unsigned     plugin_version;
		unsigned     min_core_version;
		plugin_type  type;
		std::string  path;
	};
}

#endif

