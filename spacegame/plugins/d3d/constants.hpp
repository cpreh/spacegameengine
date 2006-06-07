#ifndef SGE_D3D_CONSTANTS_HPP_INCLUDED
#define SGE_D3D_CONSTANTS_HPP_INCLUDED

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class constants {
		public:
			static const unsigned back_buffer_count = 1;
			static const bool enable_auto_depth_stencil = true;
			static D3DSWAPEFFECT swap_effect() { return D3DSWAPEFFECT_DISCARD; }
			static const DWORD flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		};
	}
}

#endif
