#ifndef SGE_D3D_TEXTURE_BASE_HPP_INCLUDED
#define SGE_D3D_TEXTURE_BASE_HPP_INCLUDED

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class renderer;
		
		class texture_base {
			friend class renderer;
		protected:
			texture_base(IDirect3DBaseTexture9* base);
			void set_base(IDirect3DBaseTexture9* base);
			virtual ~texture_base(){}
		private:
			IDirect3DBaseTexture9* base;
		};
	}
}

#endif
