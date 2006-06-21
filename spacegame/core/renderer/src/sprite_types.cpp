#include "../sprite_types.hpp"

sge::virtual_texture::virtual_texture(const rect& _area, fragmented_texture* const fragment)
	: _area(_area), fragment(fragment)
{}

sge::virtual_texture::~virtual_texture()
{
	fragment->return_fragments(*this);
}

sge::texture_ptr sge::virtual_texture::my_texture() const { return fragment->get_texture(); }

void sge::virtual_texture::set_data(const texture::const_pointer src)
{
	my_texture()->set_data(src,&_area);
}

sge::fragmented_texture::fragmented_texture(const renderer_ptr r, const texture::size_type texsize, const texture::size_type elemsize)
  : elemsize(elemsize),
    bsp(bsp_type::dim_type(texsize, texsize)),
    tex(r->create_texture(0, texsize, texsize))
{}

sge::virtual_texture_ptr sge::fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	bsp_type::iterator it = bsp.insert(bsp_type::dim_type(w,h));
	if(it == bsp.end())
		return virtual_texture_ptr();
	return virtual_texture_ptr(new virtual_texture(*it, this));
}

void sge::fragmented_texture::return_fragments(const virtual_texture& t)
{
	bsp.erase(bsp.find(t.area()));
}

