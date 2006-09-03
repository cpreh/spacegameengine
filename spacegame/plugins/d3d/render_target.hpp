#ifndef SGE_D3D_RENDER_TARGET_HPP_INCLUDED
#define SGE_D3D_RENDER_TARGET_HPP_INCLUDED

#include "../../core/renderer/render_target.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer;

class render_target : public sge::render_target, public resource {
	friend class renderer;
public:
	render_target(renderer* r, d3d_device_ptr device, size_type width, size_type height);
	size_type width() const;
	size_type height() const;
	size_type size() const;
	resource_flag_t flags() const;
private:
	void on_loss();
	void on_reset();

	void init();

	d3d_texture_ptr  tex;
	d3d_device_ptr   device;
	d3d_surface_ptr  surface;
	size_type        _width;
	size_type        _height;
};

}
}

#endif
