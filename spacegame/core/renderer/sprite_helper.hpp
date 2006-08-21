#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include "../main/types.hpp"
#include "./vertex_buffer.hpp"
#include "./index_buffer.hpp"
#include "../math/rect.hpp"
#include "./transform.hpp"

namespace sge
{

inline void fill_sprite_in_vb(vertex_buffer::iterator& it, const basic_rect<space_unit>& rsb, const basic_rect<space_unit>& rt)
{
	const basic_rect<space_unit> rs(space_x_2d_to_3d(rsb.left), space_y_2d_to_3d(rsb.top),
	                                space_x_2d_to_3d(rsb.right),space_y_2d_to_3d(rsb.bottom));

	(*it  ).pos()    = pos3(rs.left,rs.top);
	(*it++).tex()[0] = tex_pos(rt.left,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.top);
	(*it++).tex()[0] = tex_pos(rt.right,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.right,rt.bottom);

	(*it  ).pos()    = pos3(rs.left,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.left,rt.bottom);

}

inline void fill_sprite_indices(index_buffer::iterator& it, const unsigned start)
{
	(*it++) = start*0;
	(*it++) = start*1;
	(*it++) = start*2;
	(*it++) = start*0;
	(*it++) = start*2;
	(*it++) = start*3;
}

}

#endif
