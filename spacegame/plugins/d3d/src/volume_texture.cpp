#include "../../../core/main/algorithm.hpp"
#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../lock_ptr.hpp"

sge::d3d::volume_texture::volume_texture(renderer* const r, d3d_device_ptr device,
                                         const const_pointer src,
									     const size_type width, const size_type height,
									     const size_type depth, const resource_flag_t flags)
: d3d::texture_base(0), resource(r),
  device(device), lock_dest(0), flags(flags),
  width(width), height(height), depth(depth)
{
	init();
}

void sge::d3d::volume_texture::init()
{
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags);
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DVolumeTexture9* ptex;
	if(device->CreateVolumeTexture(width,height,depth,1,usage,format,pool,&ptex,0) != D3D_OK)
		throw std::runtime_error("failed to create texture");
	tex = ptex;
	set_base(tex.get());
}

void sge::d3d::volume_texture::lock(const lock_box* b)
{
	const lock_flag_t flags = LF_Discard;

	const DWORD lflags = convert_lock_flags(flags,flags);
	if(flags & RF_Dynamic || flags & RF_AutoRestore)
	{
		D3DLOCKED_BOX lb;
		if(tex->LockBox(0,&lb,0,lflags) != D3D_OK)
			throw std::runtime_error("lock texture failed");
		lock_dest = static_cast<pointer>(lb.pBits);
	}
	else
	{
		IDirect3DVolumeTexture9* temp;
		if(device->CreateVolumeTexture(get_width(),get_height(),get_depth(),1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&temp,0) != D3D_OK)
			throw std::runtime_error("creating temp texture failed");
		temp_tex = temp;
		D3DLOCKED_BOX lb;
		if(temp_tex->LockBox(0,&lb,0,lflags) != D3D_OK)
			throw std::runtime_error("lock texture failed");
		lock_dest = static_cast<pointer>(lb.pBits);
	}
}

void sge::d3d::volume_texture::unlock()
{
	if(flags & RF_Dynamic || flags & RF_AutoRestore)
	{
		if(tex->UnlockBox(0) != D3D_OK)
			throw std::runtime_error("unlock texture failed");
	}
	else
	{
		if(temp_tex->UnlockBox(0) != D3D_OK)
			throw std::runtime_error("unlock texture failed");
		if(device->UpdateTexture(temp_tex.get(),tex.get()) != D3D_OK)
			throw std::runtime_error("update texture failed");
		temp_tex = 0;
	}
	lock_dest = 0;
}

void sge::d3d::volume_texture::on_loss()
{
	if(!(flags & RF_AutoRestore))
		tex = 0;
}

void sge::d3d::volume_texture::restore()
{
	init();
}

void sge::d3d::volume_texture::set_data(const const_pointer data, const lock_box* b)
{
	lock_ptr<volume_texture> l(this,b);
	const size_type s = b ? (b->right - b->left) * (b->bottom - b->top) * (b->front - b->back) : size();
	copy(data,data+s,lock_dest);
}

sge::d3d::volume_texture::size_type sge::d3d::volume_texture::get_width() const { return width; }
sge::d3d::volume_texture::size_type sge::d3d::volume_texture::get_height() const { return height; }
sge::d3d::volume_texture::size_type sge::d3d::volume_texture::get_depth() const { return depth; }
sge::d3d::volume_texture::size_type sge::d3d::volume_texture::size() const { return get_width()*get_height()*get_depth(); }
sge::resource_flag_t sge::d3d::volume_texture::get_flags() const { return flags; }
