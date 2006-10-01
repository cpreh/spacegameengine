#ifndef SGE_D3D_ENUMERATION_HPP_INCLUDED
#define SGE_D3D_ENUMERATION_HPP_INCLUDED

#include <vector>
#include "./renderer_system.hpp"
#include "../../win32_window.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

void create_renderer_caps(unsigned adapter, d3d_ptr sys, renderer_caps& caps);

DWORD get_tnl_caps(unsigned adapter, d3d_ptr sys);

void add_display_modes(display_mode_array& v, unsigned adapter, bit_depth depth, D3DFORMAT format, d3d_ptr sys);

D3DFORMAT search_format(const display_mode& mode, d3d_ptr sys );

D3DFORMAT search_stencil_format(unsigned adapter, D3DFORMAT screen_format, d3d_ptr sys);

D3DPRESENT_PARAMETERS create_present_parameters(const renderer_parameters& param, int adapter, win32_window_ptr wnd, d3d_ptr sys);

}
}

#endif
