#include "../sprite.hpp"
#include "../system.hpp"
#include "../../renderer/lock_ptr.hpp"
#include "../helper.hpp"
#include <boost/array.hpp>

#include <iostream>

sge::sprite::sprite(sprite_system& s, const point p, const dim sz, const unsigned _z, const std::string& name, const bool vis)
	: p(p), sz(sz), _z(_z), _visible(vis), s(s), tex(s.vtexture(name)), vb_pos(s.free_vb_pos()), my_place(s.attach(*this))
{}

sge::sprite::sprite(const sprite& spr)
	: p(spr.p), sz(spr.sz), _z(spr._z), s(spr.s), tex(spr.tex), vb_pos(s.free_vb_pos()), my_place(s.attach(*this))
{}

void sge::sprite::set_texture(const std::string& name) { tex = s.vtexture(name); }

sge::sprite::~sprite() { s.detach(*this); }

void sge::sprite::update()
{
	update_where(s.vb->begin()+vb_pos);
}

void sge::sprite::update_where(vertex_buffer::iterator it)
{
	const lock_rect& area = tex->area();

	const rect rt(space_unit(area.left)  / s.texsize, space_unit(area.top)    / s.texsize,
		      space_unit(area.right) / s.texsize, space_unit(area.bottom) / s.texsize);

	std::cerr << get_rect() << '\n';

	fill_sprite_in_vb(it, get_rect(), rt);
}

sge::index_buffer::iterator sge::sprite::update_ib(index_buffer::iterator it)
{
	fill_sprite_indices(it,vb_pos);
	return it;
}

void sge::sprite::draw()
{
	if(!tex)
		return;
	{
		boost::array<vertex_buffer::value_type,sizeof(space_unit)*5*4> buf; // FIXME: magic constants
		update_where(s.vb->create_iterator(buf.c_array()));
		s.vb->set_data(buf.data(),vb_pos,4);
	}
	{
		boost::array<index_buffer::value_type, detail::indices_per_sprite> buf;
		update_ib(buf.c_array());
		s.ib->set_data(buf.data(), 0, detail::indices_per_sprite);
	}
	s.set_parameters();
	s.r->set_texture(0,tex->my_texture());
	s.r->render(s.vb,s.ib,0,4,PT_Triangle,2);
}

sge::texture_ptr sge::sprite::get_texture() const { return tex ? tex->my_texture() : texture_ptr(); }

bool sge::sprite::equal_texture(const sprite& l, const sprite& r)
{
	return l.get_texture() == r.get_texture();
}

bool sge::sprite::less(const sprite& l, const sprite& r)
{
	const bool lvis = l.visible(), rvis = r.visible();
	const unsigned lz = l.z(), rz = r.z();
	sge::texture_ptr ltex = l.get_texture(), rtex = r.get_texture();

	if(lvis != rvis)
		return lvis > rvis;
	if(lz != rz)
		return lz > rz;
	if(ltex != rtex)
		return ltex < rtex;
	return false;
}

