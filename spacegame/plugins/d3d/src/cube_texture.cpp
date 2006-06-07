#include "../cube_texture.hpp"
#include "../lock_ptr.hpp"
#include "../../../core/main/algorithm.hpp"

sge::d3d::cube_texture::cube_texture(renderer* const r, d3d_device_ptr device,
                                     const cube_side_src_array* data,
									 const size_type sz, const resource_flag_t flags)
:   d3d::texture_base(0), resource(r),
	device(device), flags(flags), sz(sz), lock_dest(0)
{
	init(data);
}

void sge::d3d::cube_texture::init(const cube_side_src_array* src)
{
	if(!src)
		return;
	const cube_side_src_array& data = *src;
	for(cube_side_src_array::size_type s = 0; s < data.size(); ++s)
	{
		lock_ptr<cube_texture> l(this,cube_side(s));
		copy(data[s],data[s]+size(),lock_dest);
	}
}

void sge::d3d::cube_texture::lock(const cube_side side, const lock_rect* const r)
{
}

void sge::d3d::cube_texture::unlock()
{
}

void sge::d3d::cube_texture::set_data(const cube_side side, const const_pointer data, const lock_rect* const r)
{

}

sge::resource_flag_t sge::d3d::cube_texture::get_flags() const { return flags; }
sge::cube_texture::size_type sge::d3d::cube_texture::size() const { return sz; }

void sge::d3d::cube_texture::on_loss()
{
	if(!(flags & RF_AutoRestore))
		tex = 0;
}

void sge::d3d::cube_texture::restore()
{
	init();
}
