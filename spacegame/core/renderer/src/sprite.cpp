#include "../sprite.hpp"
#include "../sprite_system.hpp"
#include "../lock_ptr.hpp"
#include "../transform.hpp"
#include <iostream>
#include <boost/array.hpp>


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
	const virtual_texture::rect& area = tex->area();

	const rect rt(space_unit(area.left)  / s.texsize, space_unit(area.top)    / s.texsize,
		      space_unit(area.right) / s.texsize, space_unit(area.bottom) / s.texsize),

	           rs(space_x_2d_to_3d(x())        ,space_y_2d_to_3d(y()),
	              space_x_2d_to_3d(x()+width()),space_y_2d_to_3d(y()+height()));

	(*it  ).pos()    = pos3(rs.left,rs.top);
	(*it++).tex()[0] = tex_pos(rt.left,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.top);
	(*it++).tex()[0] = tex_pos(rt.right,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.right,rt.bottom);

	(*it  ).pos()    = pos3(rs.left,rs.bottom);
	(*it  ).tex()[0] = tex_pos(rt.left,rt.bottom);
}

sge::index_buffer::iterator sge::sprite::update_ib(index_buffer::iterator it)
{
	(*it++) = vb_pos + 0;
	(*it++) = vb_pos + 1;
	(*it++) = vb_pos + 2;
	(*it++) = vb_pos + 0;
	(*it++) = vb_pos + 2;
	(*it++) = vb_pos + 3;
	return it;
}

void sge::sprite::draw()
{
	if(!tex)
		return;
	{
		boost::array<char,sizeof(float)*5*4> buf;
		update_where(s.vb->create_iterator(buf.c_array()));
		s.vb->set_data(buf.data(),vb_pos,4);
	}
	{
		boost::array<index_buffer::value_type,6> buf;
		update_ib(buf.c_array());
		s.ib->set_data(buf.data(),0,6);
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

