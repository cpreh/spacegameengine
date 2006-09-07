#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/transform.hpp"
#include "./types.hpp"

#include <iostream>

namespace sge
{

inline void fill_sprite_in_vb(vertex_buffer::iterator& it, const rect& rsb, const rect& rt)
{
	const rect rs(space_rect_2d_to_3d(rsb));

	std::cerr << rs << ' ' << rt << '\n';

	(*it  ).pos()    = pos3(rs.left,rs.top);
	(*it++).tex()[0] = tex_pos(rt.left,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.top);
	(*it++).tex()[0] = tex_pos(rt.right,rt.top);

	(*it  ).pos()    = pos3(rs.right,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.right,rt.bottom);

	(*it  ).pos()    = pos3(rs.left,rs.bottom);
	(*it++).tex()[0] = tex_pos(rt.left,rt.bottom);

}

inline void fill_sprite_indices(index_buffer::iterator& it, const index_buffer::value_type start)
{
	std::cerr << start << '\n';
	(*it++) = start + 0;
	(*it++) = start + 1;
	(*it++) = start + 2;
	(*it++) = start + 0;
	(*it++) = start + 2;
	(*it++) = start + 3;
}

}

#endif
