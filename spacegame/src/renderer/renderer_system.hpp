#ifndef SGE_RENDER_ERSYSTEM_HPP_INCLUDED
#define SGE_RENDER_ERSYSTEM_HPP_INCLUDED

#include <vector>
#include "../main/shared_ptr.hpp"
#include "../main/types.hpp"
#include "./renderer_types.hpp"
#include "./renderer.hpp"

namespace sge
{

typedef std::vector<renderer_caps> renderer_caps_array;

class renderer_system {
public:
	enum { use_best_renderer = -1 };
	virtual renderer_ptr create_renderer(const renderer_parameters& param,
	                                     int adapter = use_best_renderer) = 0;
	virtual void get_renderer_caps(renderer_caps_array& v) const = 0;
	virtual ~renderer_system(){}
};

typedef shared_ptr<renderer_system> renderer_system_ptr;

}

#endif
