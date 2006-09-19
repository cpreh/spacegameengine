#include "../../../ptr_cast.hpp"
#include "../../../util.hpp"
#include "../../../renderer/renderer_types.hpp"
#include "../renderer_system.hpp"
#include "../conversion.hpp"
#include "../renderer.hpp"
#include "../constants.hpp"
#include "../enumeration.hpp"

sge::d3d::renderer_system::renderer_system()
{
	sys = Direct3DCreate9(D3D_SDK_VERSION);
	if(!sys)
		throw std::runtime_error("Initialization of d3d failed");
}

void sge::d3d::renderer_system::get_renderer_caps(renderer_caps_array& v) const
{
	const unsigned adapter_count = sys->GetAdapterCount();
	for(unsigned ad = 0; ad < adapter_count; ++ad)
	{
		renderer_caps c;
		create_renderer_caps(ad,sys,c);
		v.push_back(c);
	}
}

sge::renderer_ptr sge::d3d::renderer_system::create_renderer(const renderer_parameters& param, int adapter)
{
	if(adapter == use_best_renderer)
	{
		// TODO: search for best renderer
		adapter = 0;
	}

	win32_window_ptr wnd = new win32_window(0,0,param.mode.width,param.mode.height);
	const DWORD tnl_flags = get_tnl_caps(adapter,sys);
	D3DPRESENT_PARAMETERS pp = create_present_parameters(param,adapter,wnd,sys);

	IDirect3DDevice9* device;
	if(sys->CreateDevice(adapter,D3DDEVTYPE_HAL,wnd->get_hwnd(),tnl_flags,&pp,&device) != D3D_OK)
		throw std::runtime_error("Failed to initialize the renderer");
	ShowCursor(FALSE);

	return new renderer(device,param,adapter,wnd,sys);
}
