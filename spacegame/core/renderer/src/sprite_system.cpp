#include <algorithm>
#include <stdexcept>
#include "../sprite_system.hpp"
#include "../../renderer/vertex_format.hpp"
#include "../../renderer/lock_ptr.hpp"

namespace
{

void default_texture_not_present_handler(const std::string& s)
{
	throw std::runtime_error(std::string("texture \"") + s + "\" not present in sprite_system! (default handler)");
}

}

template<typename NewArg1, typename NewArg2, typename Fun>
	class binary_dereference_binder : public std::binary_function<NewArg1,NewArg2,typename Fun::result_type> {
public:
	binary_dereference_binder(const Fun& f)
		: f(f) {}
	typename Fun::result_type operator()(NewArg1 arg1, NewArg2 arg2) const { return f(*arg1,*arg2); }
private:
	Fun f;
};

template<typename NewArg1, typename Fun>
	class unary_dereference_binder : public std::unary_function<NewArg1,typename Fun::result_type> {
public:
	unary_dereference_binder(const Fun& f)
		: f(f) {}
	typename Fun::result_type operator()(NewArg1 arg) const { return t(*arg); }
private:
	Fun f;
};

template<typename NewArg1, typename NewArg2, typename Fun>
	binary_dereference_binder<NewArg1,NewArg2,Fun> dereference_binder(const Fun& f)
{
	return binary_dereference_binder<NewArg1,NewArg2,Fun>(f);
}

template<typename NewArg1, typename Fun>
	unary_dereference_binder<NewArg1,Fun> dereference_binder(const Fun& f)
{
	return unary_dereference_binder<NewArg1,Fun>(f);
}

sge::sprite_system::sprite_system(const renderer_ptr r, const texture::size_type tex_size_pow2, const texture::size_type elements_per_row, const handler_function handler)
  : texture_not_present_handler(handler == 0 ? default_texture_not_present_handler : handler),
    r(r),
    texsize(pow_int(2,tex_size_pow2)),
    elemsize(texsize/elements_per_row)
{
	const unsigned init_sprites = 25;
	resource_flag_t rf = RF_WriteOnly | RF_Dynamic;
	vb = r->create_vertex_buffer(vertex_format().add(VU_Pos).add(VU_Tex),init_sprites*4,rf);
	ib = r->create_index_buffer(init_sprites*6);
	free_pos.reserve(init_sprites);
	for(unsigned i = 0; i < init_sprites; ++i)
		free_pos.push_back(i*4);
}

sge::vertex_buffer::size_type sge::sprite_system::free_vb_pos()
{
	if(free_pos.empty())
	{
		const vertex_buffer::size_type new_size = vb->size()*2;
		free_pos.reserve(new_size/4);
		for(unsigned i = vb->size(); i < new_size; i+=4)
			free_pos.push_back(i);
		vb->resize(new_size);
		ib->resize(ib->size()*2);
	}
	const vertex_buffer::size_type vb_pos = free_pos.back();
	free_pos.pop_back();
	return vb_pos;
}

sge::sprite_list::iterator sge::sprite_system::attach(sprite& s)
{
	sprites.push_back(&s);
	return --sprites.end();
}

void sge::sprite_system::detach(const sprite& s)
{
	free_pos.push_back(s.vb_pos);
	sprites.erase(s.my_place);
}

bool sge::sprite_system::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h, const std::string& name)
{
	if(virtual_textures.find(name) != virtual_textures.end())
		return false;

	for(fragmented_texture_list::iterator it = fragmented_textures.begin(); it != fragmented_textures.end(); ++it)
		if(virtual_texture_ptr p = (*it)->consume_fragments(w,h))
			return insert_texture(p,name), true;
		
	fragmented_textures.push_back(fragmented_texture_ptr(new fragmented_texture(r, texsize, elemsize)));
	if(virtual_texture_ptr p = fragmented_textures.back()->consume_fragments(w,h))
		return insert_texture(p,name), true;
	// give up
	throw std::runtime_error("sprite_system::add_texture: failed to allocate texture!");
}

bool sge::sprite_system::add_texture(const image_ptr im, const std::string& name)
{
	return add_texture(im->data(),im->width(),im->height(),name);
}

bool sge::sprite_system::remove_texture(const std::string& name)
{
}

void sge::sprite_system::clear()
{
}

void sge::sprite_system::draw()
{
	sprites.sort(dereference_binder<const sprite*,const sprite*>(std::ptr_fun(sprite::less)));
	{
		lock_ptr<index_buffer> l(ib.get(),LF_Discard);
		index_buffer::iterator it = ib->begin();
		for(sprite_list::iterator sit = sprites.begin(); sit != sprites.end(); ++sit)
			it = (*sit)->update_ib(it);
	}

	lock_ptr<vertex_buffer> l(vb.get(),LF_Discard);
	std::for_each(sprites.begin(),sprites.end(),std::mem_fun(&sprite::update));

	set_parameters();
	
	unsigned first_index = 0;
	for(sprite_list::iterator it = sprites.begin(); it != sprites.end() && (*it)->visible(); )
	{
		unsigned num_objects;
		it = first_mismatch(it, sprites.end(), num_objects, dereference_binder<const sprite*, const sprite*>(std::ptr_fun(sprite::equal_texture)));
		if((*it)->get_texture())
		{
			r->set_texture(0,(*it)->get_texture());
			r->render(vb,ib,0,unsigned(vb->size()),PT_Triangle,num_objects*2,first_index);
		}
		first_index += num_objects * 6;
	}
}

void sge::sprite_system::set_parameters()
{
	r->set_matrix(MU_Camera,matrix4x4<space_unit>());
	r->set_matrix(MU_Projection,matrix_ortogonal_xy<space_unit>());
	r->set_texture_stage_op(  0, SOP_Color,   SOPV_SelectArg1);
	r->set_texture_stage_arg( 0, SARG_Color1, SARGV_Texture);
	r->set_texture_stage_op(1,SOP_Color,SOPV_Disable);
	r->set_filter_state(0,FARG_MagFilter,FARGV_Linear);							
}

/*const sge::texture_fragment* sge::sprite_system::get_texture_fragment(const std::string& name)
{
	if(name == no_texture)
		return 0;
	
	texture_fragment_map::const_iterator it = fragments.find(name);
	if(it == fragments.end())
	{
		texture_not_present_handler(name);
		it = fragments.find(name);
		if(it == fragments.end())
			throw std::logic_error(std::string("texture_not_present_handler in sprite_system failed") += name);
	}
	return it->second;
}*/

const char* const sge::sprite_system::no_texture = "";

sge::fragmented_texture::fragmented_texture(const renderer_ptr r, const texture::size_type texsize, const texture::size_type elemsize)
  : elemsize(elemsize),
    fragments(texsize / elemsize, texsize / elemsize, true),
    tex(r->create_texture(0, texsize, texsize))
{}

sge::virtual_texture_ptr sge::fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	const texture::size_type dw = round_div_int(w, elemsize),
	                         dh = round_div_int(h, elemsize);
	
}

void sge::fragmented_texture::return_fragments(const virtual_texture& t)
{
	typedef virtual_texture::rect rect;

	const rect& r = t.lock_area();
	const rect assign_rect(r.left / elemsize,
	                       r.top / elemsize,
	                       round_div_int(r.right, elemsize),
	                       round_div_int(r.bottom, elemsize));
	fragments.assign_rect(assign_rect,true);
}

