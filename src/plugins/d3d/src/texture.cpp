#include "../../../algorithm.hpp"
#include "../lock_ptr.hpp"
#include "../texture.hpp"
#include "../conversion.hpp"

sge::d3d::texture::texture(renderer* const r, d3d_device_ptr device, const const_pointer data, const size_type _width, const size_type _height, const unsigned mip_levels, const resource_flag_t nflags)
: d3d::texture_base(0), resource(r, nflags & RF_Dynamic),
  device(device), _flags(nflags), _width(_width), _height(_height),
  mip_levels(mip_levels), lock_dest(0)
{
	init();
}

void sge::d3d::texture::init()
{
	const DWORD usage = flags & RF_Dynamic ? D3DUSAGE_DYNAMIC : 0;
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags());
	const D3DFORMAT format = D3DFMT_A8R8G8B8;

	IDirect3DTexture9* ptex;
	if(device->CreateTexture(width,height,mip_levels,usage,format,pool,&ptex,0) != D3D_OK)
		throw std::runtime_error("failed to create texture");
	tex = ptex;
	set_base(tex.get());
}

void sge::d3d::texture::lock(const lock_rect* const r)
{
	const lock_flag_t _lflags = LF_Discard;
	const DWORD lflags = convert_lock_flags(_lflags, flags());
	if(flags() & RF_Dynamic)
	{
		D3DLOCKED_RECT lr;
		if(tex->LockRect(0,&lr,reinterpret_cast<const RECT*>(r),lflags) != D3D_OK)
			throw std::runtime_error("lock texture failed");
		lock_dest = static_cast<pointer>(lr.pBits);
	}
	else
	{
		IDirect3DTexture9* temp;
		if(device->CreateTexture(width(),height(),1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&temp,0) != D3D_OK)
			throw std::runtime_error("creating temp texture failed");
		temp_tex = temp;
		D3DLOCKED_RECT lr;
		if(temp_tex->LockRect(0,&lr,0,lflags) != D3D_OK)
			throw std::runtime_error("lock texture failed");
		lock_dest = static_cast<pointer>(lr.pBits);
	}
}

void sge::d3d::texture::unlock()
{
	if(flags() & RF_Dynamic)
	{
		if(tex->UnlockRect(0) != D3D_OK)
			throw std::runtime_error("unlock texture failed");
	}
	else
	{
		if(temp_tex->UnlockRect(0) != D3D_OK)
			throw std::runtime_error("unlock texture failed");
		if(device->UpdateTexture(temp_tex.get(),temp_tex.get()) != D3D_OK)
			throw std::runtime_error("update texture failed");
		temp_tex = 0;
	}
	lock_dest = 0;
}

void sge::d3d::texture::on_loss()
{
	tex = 0;
}

void sge::d3d::texture::on_reset()
{
	init();
}

void sge::d3d::texture::set_data(const const_pointer data, const lock_rect* const r)
{
	lock_ptr<texture> l(this,r);
	const size_type s = r ? width(*r) * height(*r) : size();
	copy(data,data+s,lock_dest);
}

sge::d3d::texture::size_type sge::d3d::texture::width() const
{
	return width;
}

sge::d3d::texture::size_type sge::d3d::texture::height() const
{
	return height;
}

sge::d3d::texture::size_type sge::d3d::texture::size() const
{
	return width()*height();
}

sge::resource_flag_t sge::d3d::texture::flags() const
{
	return _flags;
}
