#ifndef SGE_D3D_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_D3D_CUBE_TEXTURE_HPP_INCLUDED

#include "../../core/renderer/cube_texture.hpp"
#include "./resource.hpp"
#include "./texture_base.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class cube_texture : public d3d::texture_base, public sge::cube_texture, public resource {
	friend class renderer;
private:
	cube_texture(renderer* r, d3d_device_ptr device, const cube_side_src_array* data, size_type sz, resource_flag_t flags);
public:
	size_type size() const;
	resource_flag_t flags() const;
	void set_data(cube_side side, const_pointer p, const lock_rect* r = 0);
	void lock(cube_side side, const lock_rect* r = 0);
	void unlock();
private:
	void on_loss();
	void on_reset();

	void init(const cube_side_src_array* data = 0);

	d3d_device_ptr        device;
	d3d_cube_texture_ptr  tex;
	resource_flag_t       _flags;
	size_type             sz;
	pointer               lock_dest;
};

}
}

#endif
