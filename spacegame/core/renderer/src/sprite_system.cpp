#include <algorithm>
#include <stdexcept>
#include "../sprite_system.hpp"
#include "../vertex_format.hpp"
#include "../lock_ptr.hpp"
#include "../../main/functional.hpp"

namespace
{

void default_texture_not_present_handler(const std::string& s)
{
	throw std::runtime_error(std::string("texture \"") + s + "\" not present in sprite_system! (default handler)");
}

}

sge::sprite_system::sprite_system(const renderer_ptr r, const handler_function handler)
  : texture_not_present_handler(handler == 0 ? default_texture_not_present_handler : handler),
    r(r),
    texsize(512) // TODO: let the driver determinate the best texture size
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
			return insert_texture(p,src,name), true;
		
	fragmented_textures.push_back(fragmented_texture_ptr(new fragmented_texture(r, texsize)));
	if(virtual_texture_ptr p = fragmented_textures.back()->consume_fragments(w,h))
		return insert_texture(p,src,name), true;
	// TODO: ask the driver if a texture this big can be created and do it
	throw std::runtime_error(std::string("sprite_system::add_texture(): failed to allocate texture \"") += name + "\" (texture may be too big)!");
}

bool sge::sprite_system::add_texture(const image_ptr im, const std::string& name)
{
	return add_texture(im->data(),im->width(),im->height(),name);
}

void sge::sprite_system::insert_texture(const virtual_texture_ptr t, const texture::const_pointer src, const std::string& name)
{
	t->set_data(src);
	virtual_textures[name] = t;
}

bool sge::sprite_system::remove_texture(const std::string& name)
{
	virtual_texture_map::iterator it = virtual_textures.find(name);
	if(it == virtual_textures.end())
		return false;
	virtual_textures.erase(it);
	return true;
}

void sge::sprite_system::clear()
{
	virtual_textures.clear();
}

void sge::sprite_system::draw()
{
	sprites.sort(dereference_binder<const sprite*,const sprite*>(std::ptr_fun(sprite::less)));
	{
		lock_ptr<index_buffer_ptr> l(ib,LF_Discard);
		index_buffer::iterator it = ib->begin();
		for(sprite_list::iterator sit = sprites.begin(); sit != sprites.end(); ++sit)
			it = (*sit)->update_ib(it);
	}

	{
		lock_ptr<vertex_buffer_ptr> l(vb,LF_Discard);
		std::for_each(sprites.begin(),sprites.end(),std::mem_fun(&sprite::update));
	}

	set_parameters();
	
	unsigned first_index = 0;
	for(sprite_list::iterator it = sprites.begin(); it != sprites.end() && (*it)->visible(); )
	{
		unsigned num_objects;
		sprite_list::iterator next = first_mismatch_if(it, sprites.end(), num_objects, dereference_binder<const sprite*, const sprite*>(std::ptr_fun(sprite::equal_texture)));
		if((*it)->get_texture())
		{
			r->set_texture(0,(*it)->get_texture());
			r->render(vb,ib,0,unsigned(vb->size()),PT_Triangle,num_objects*2,first_index);
		}
		first_index += num_objects * 6;
		it = next;
	}
}

void sge::sprite_system::set_parameters()
{
	r->set_transformation(matrix4x4<space_unit>());
	r->projection_orthogonal();
//	r->set_texture_stage_op(  0, SOP_Color,   SOPV_SelectArg1);
//	r->set_texture_stage_arg( 0, SARG_Color1, SARGV_Texture);
//	r->set_texture_stage_op(1,SOP_Color,SOPV_Disable);
	r->set_filter_state(0,FARG_MagFilter,FARGV_Linear);							
}

sge::virtual_texture_ptr sge::sprite_system::vtexture(const std::string& name) const
{
	if(name == no_texture)
		return virtual_texture_ptr();
	
	virtual_texture_map::const_iterator it = virtual_textures.find(name);
	if(it == virtual_textures.end())
	{
		texture_not_present_handler(name);
		it = virtual_textures.find(name);
		if(it == virtual_textures.end())
			throw std::logic_error(std::string("texture_not_present_handler in sprite_system failed for texture \"") += name + "\"!");
	}
	return it->second;
}

const char* const sge::sprite_system::no_texture = "";
