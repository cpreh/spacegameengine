#include "../texture_base.hpp"

sge::d3d::texture_base::texture_base(IDirect3DBaseTexture9* base)
: base(base)
{}

void sge::d3d::texture_base::set_base(IDirect3DBaseTexture9* b)
{
	base = b;
}
