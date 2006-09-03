#include "../render_target.hpp"

sge::d3d::render_target::render_target(renderer* const r, const d3d_device_ptr device, const size_type _width, const size_type _height)
: resource(r, true),
  device(device), _width(_width), _height(_height)
{
	init();
}

void sge::d3d::render_target::init()
{
	IDirect3DTexture9* t;
	if(device->CreateTexture(width(),height(),1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&t,0) != D3D_OK)
		throw std::runtime_error("creating render target failed");
	tex = t;
	IDirect3DSurface9* s;
	if(tex->GetSurfaceLevel(0,&s) != D3D_OK)
		throw std::runtime_error("getting surface for render target failed");
	surface = s;
}

void sge::d3d::render_target::on_loss()
{
	surface = 0;
	tex = 0;
}

void sge::d3d::render_target::on_reset()
{
	init();
}

sge::d3d::render_target::size_type sge::d3d::render_target::size() const
{
	return width()*height();
}

sge::d3d::render_target::size_type sge::d3d::render_target::width() const
{
	return _width;
}

sge::d3d::render_target::size_type sge::d3d::render_target::height() const
{
	return _height;
}

sge::resource_flag_t sge::d3d::render_target::flags() const
{
	return RF_None;
}
