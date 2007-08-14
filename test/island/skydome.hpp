#ifndef SKYDOME_HPP_INCLUDED
#define SKYDOME_HPP_INCLUDED

#include "../../src/renderer/renderer.hpp"
#include "../../src/math/vector.hpp"

class skydome
{
	public:
	typedef sge::space_unit     space_type;
	typedef int                 rep_type;

	skydome(const space_type radius,const rep_type,const rep_type,const sge::renderer_ptr,const sge::texture_ptr); 
	void draw();

	private:
	const space_type            radius;
	const rep_type              y_reps,z_reps;
	const rep_type              triangle_count,index_count;
	const sge::renderer_ptr     rend;
	const sge::texture_ptr      texture;
	sge::vertex_buffer_ptr      vb;
	sge::index_buffer_ptr       ib;

	sge::math::vector3 point(rep_type y,rep_type z) const;
	void generate_index_buffer();
	void generate_vertex_buffer();
};

#endif // SKYDOME_HPP_INCLUDED
