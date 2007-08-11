#include "../../src/renderer/lock_ptr.hpp"
#include "../../src/math/constants.hpp"
#include "../../src/exception.hpp"
#include "skydome.hpp"

namespace
{
sge::math::vector3 cross(const sge::math::vector3 &a,const sge::math::vector3 &b)
{
	return sge::math::vector3(a.y()*b.z() - a.z()*b.y(),
                            a.z()*b.x() - a.x()*b.z(),
                            a.x()*b.y() - a.y()*b.x());
}
}

skydome::skydome(const skydome::space_type radius,const skydome::rep_type y_reps,const skydome::rep_type z_reps,const sge::renderer_ptr rend,const sge::texture_ptr texture) 
	: radius(radius),y_reps(y_reps),z_reps(z_reps),triangle_count(((z_reps-1) * 2 - 1) * y_reps),index_count(triangle_count*3),rend(rend),texture(texture)
{
	if (y_reps <= 0 || z_reps <= 0)
		throw sge::exception("invalid detail parameters to sky dome");

	generate_vertex_buffer();
	generate_index_buffer();
}

void skydome::draw()
{
	rend->set_texture(texture);
	rend->render(vb,ib,0,vb->size(),sge::indexed_primitive_type::triangle,triangle_count,0);
}

sge::math::vector3 skydome::point(skydome::rep_type y,skydome::rep_type z) const 
{
	// TODO: Den Modulokrams ueberdenken
	if (y < 0) y = y % y_reps;
	if (z < 0) z = z % z_reps;

	const space_type z_angle = space_type(z)/space_type(z_reps)*space_type(sge::math::PI)*space_type(0.5);
	const space_type y_angle = space_type(y)/space_type(y_reps)*space_type(sge::math::PI)*space_type(2);
	return sge::math::vector3(radius * std::sin(z_angle) * std::cos(y_angle),radius * std::cos(z_angle),radius * std::sin(z_angle) * std::sin(y_angle));
}

void skydome::generate_index_buffer()
{
	ib = rend->create_index_buffer(triangle_count * 3);
	sge::lock_ptr<sge::index_buffer_ptr> _lock(ib);


	const rep_type vertex_count = vb->size();
	sge::index_buffer::iterator ibit = ib->begin();
	for (rep_type y = 0,cur = 0; y < y_reps; ++y)
	{
		// Oberstes Dreieck. Die Z-Schritte gehen von senkrecht nach oben bis zur Horizontalen, also im Uhrzeigersinn
		*ibit++ = cur;
		*ibit++ = cur+1;
		// "gegenueber"
		*ibit++ = (cur+1+z_reps)%vertex_count;

		cur++;

		// Alle weiteren Dreiecke
		for (rep_type z = 0; z < z_reps-2; ++z)
		{
			// Erstes Dreieck
			*ibit++ = cur;
			*ibit++ = cur+1;
			*ibit++ = (cur+1+z_reps)%vertex_count;

			// Zweites Dreieck
			*ibit++ = (cur+1+z_reps)%vertex_count;
			*ibit++ = (cur+z_reps)%vertex_count;
			*ibit++ = cur;

			cur++;
		}

		cur++;
	}
}

void skydome::generate_vertex_buffer()
{
	vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex).add(sge::vertex_usage::normal), y_reps * z_reps);
	sge::lock_ptr<sge::vertex_buffer_ptr> _lock(vb);

	sge::vertex_buffer::iterator vbit = vb->begin();
	for (rep_type y = 0; y < y_reps; ++y)
	{
		for (rep_type z = 0; z < z_reps; ++z)
		{
			vbit->pos() = point(y,z);

			// Ganz oben? Dann trivial
			if (z == 0)
			{
				vbit->normal() = sge::math::vector3(0,1,0);
			}
			// Ganz unten?
			else if (z == (z_reps-1))
			{
				sge::math::vector3 self(0,-1,0),
													 right = point(y+1,z) - vbit->pos(),
													 left = point(y-1,z) - vbit->pos();
				vbit->normal() = sge::math::normalize(cross(self,left) + cross(right,self));
			}
			else
			{
				// Mittendrin?
				sge::math::vector3 before = point(y,z-1) - vbit->pos(),
													 after = point(y,z+1) - vbit->pos(),
													 left = point(y-1,z) - vbit->pos(),
													 right = point(y+1,z) - vbit->pos();

				sge::math::vector3 n0 = cross(left,before),n1 = cross(after,left),n2 = cross(right,after),n3 = cross(before,right);
				// TODO: Muss man die einzelnen Normalen wirklich normalisieren?
				n0.normalize(),n1.normalize(),n2.normalize(),n3.normalize();
				vbit->normal() = sge::math::normalize(n0 + n1 + n2 + n3);
			}

			vbit->tex() = sge::math::vector2((vbit->normal().x()+1)/2,(vbit->normal().z()+1)/2);
			vbit++;
		}
	}
}
