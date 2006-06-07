#include "../extensions.hpp"
#include <stdexcept>

void sge::ogl::load_extensions()
{
	static bool extensions_loaded = false;
	if(!extensions_loaded)
	{
		if(glewInit() != GLEW_OK)
			throw std::runtime_error("glewInit() failed");
		extensions_loaded = true;
	}

}
