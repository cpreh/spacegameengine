#ifndef SGE_OGL_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_OGL_RENDERER_SYSTEM_HPP_INCLUDED

#include "../../renderer/renderer_system.hpp"

namespace sge
{
namespace ogl
{

class renderer_system : public sge::renderer_system {
public:
	renderer_ptr create_renderer(const renderer_parameters& param, int adapter);
	void get_renderer_caps(renderer_caps_array& v) const;

};

}
}

#endif
