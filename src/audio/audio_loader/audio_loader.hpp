#ifndef SGE_AUDIO_HPP_INCLUDED
#define SGE_AUDIO_HPP_INCLUDED

// C++
#include <vector>
#include <string>
// sge
#include "../../shared_ptr.hpp"
#include "../../plugin_traits.hpp"
// Own stuff
#include "audio_file.hpp"

namespace sge
{
class audio_loader
{
	public:
	virtual shared_ptr<audio_file> load(const std::string &filename) = 0;
	virtual bool is_valid_file(const std::string &filename) const = 0;
	virtual audio_loader() {}
};

namespace detail
{

template<> struct plugin_traits<audio_loader> {
	static const char* plugin_loader_name() { return "create_audio_loader"; }
	static plugin_type get_plugin_type() { return PT_AudioLoader; }
	typedef audio_loader* (*loader_fun)();
};

}

}

#endif // AUDIO_HPP
