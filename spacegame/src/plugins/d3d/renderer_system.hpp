#ifndef SGE_D3D_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_D3D_RENDERER_SYSTEM_HPP_INCLUDED

#include "../../core/renderer/renderer_system.hpp"
#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer_system : public sge::renderer_system {
public:
	renderer_system();
	renderer_ptr create_renderer(const renderer_parameters& param, int adapter);
	void get_renderer_caps(renderer_caps_array& v) const;
private:
	d3d_ptr sys;
};

}
}

#endif
