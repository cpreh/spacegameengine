// C
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
// C++
#include <iostream>
#include <map>
#include <boost/shared_array.hpp>
#include <boost/lexical_cast.hpp>
// sge
#include <sge/math/matrix.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/plugin.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/renderer/renderer_system.hpp>
#include <sge/input/input_system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/timer.hpp>
#include <sge/image/image_loader.hpp>
#include <sge/image/image.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/lock_ptr.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/rect.hpp>
#include <sge/media.hpp>
#include <sge/accessor.hpp>
#include <ctime>
#include <cstdlib>

sge::math::vector3 cross(const sge::math::vector3 &a,const sge::math::vector3 &b)
{
	return sge::math::vector3(a.y()*b.z() - a.z()*b.y(),
                            a.z()*b.x() - a.x()*b.z(),
                            a.x()*b.y() - a.y()*b.x());
}

int main()
{
	std::srand(std::time(0));

	sge::plugin_manager pm;
	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();
	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr image_loader(image_loader_plugin->get()());

	const sge::renderer_system_ptr rs(renderer_plugin->get()());

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	sge::key_state_tracker ks(is);
	sge::timer frame_timer(1000);

	// Vertexbuffer erstellen
	//const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex), heightmap->height() * heightmap->width());

	unsigned y_reps = 32,z_reps = 8;
	sge::space_unit r = 3;

	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex).add(sge::vertex_usage::normal), y_reps * z_reps);
	{
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(model_vb);
		sge::vertex_buffer::iterator vbit = model_vb->begin();

		for (unsigned y = 0; y < y_reps; ++y)
		{
			for (unsigned z = 0; z < z_reps; ++z)
			{
				sge::space_unit z_angle = sge::space_unit(z)/sge::space_unit(z_reps)*sge::math::PI*0.5;
				sge::space_unit y_angle = sge::space_unit(y)/sge::space_unit(y_reps)*sge::math::PI*2;
				vbit->pos() = sge::math::vector3(r * std::sin(z_angle) * std::cos(y_angle),r * std::cos(z_angle),r * std::sin(z_angle) * std::sin(y_angle));
				vbit++;
				//vbit->tex() = (sge::math::vector2(vbit->pos().x(),vbit->pos().z()) - sge::math::vector2(-r,-r)) * (sge::space_unit(1)/(2*r));


				/*
				vbit->tex().y() = std::acos(vbit->pos().z()/r) / sge::math::PI;
				if (vbit->pos().y() >= 0)
					vbit->tex().x() = std::acos(vbit->pos().x()/(r * std::sin(sge::math::PI*(vbit->tex().y())))) / 2*sge::math::PI;
				else
					vbit->tex().x() = (sge::math::PI + std::acos(vbit->pos().x()/(r * std::sin(sge::math::PI*vbit->tex().y())))) / 2*sge::math::PI;
				vbit++;
				*/
			}
		}

		vbit = model_vb->begin();
		for (unsigned cur = 0; cur < model_vb->size(); ++cur)
		{
			// Ganz oben? Dann trivial
			if (cur % z_reps == 0)
			{
				vbit->normal() = sge::math::vector3(0,1,0);
				vbit++;
				continue;
			}

			// Ganz unten?
			if (cur % z_reps == z_reps - 1)
			{
				sge::math::vector3 self(0,-1,0),
												   right = (*model_vb)[(cur+z_reps) % model_vb->size()].pos() - vbit->pos(),
												   left = (*model_vb)[(cur-z_reps) % model_vb->size()].pos() - vbit->pos();

				//std::cout << "Ganz unten. self" << self << ",left" << left << ",n" << cross(self,left) << "\n";

				vbit->normal() = sge::math::normalize(cross(self,left) + cross(right,self));
				vbit++;
				continue;
			}

			assert(cur > 0);

			// Mittendrin?
			sge::math::vector3 before = (*model_vb)[cur-1].pos() - vbit->pos(),
			                   after = (*model_vb)[cur+1].pos() - vbit->pos(),
												 left = (*model_vb)[(cur-z_reps) % model_vb->size()].pos() - vbit->pos(),
												 right = (*model_vb)[(cur+z_reps) % model_vb->size()].pos() - vbit->pos();

			sge::math::vector3 n0 = cross(left,before),n1 = cross(after,left),n2 = cross(right,after),n3 = cross(before,right);
			n0.normalize(),n1.normalize(),n2.normalize(),n3.normalize();
			vbit->normal() = sge::math::normalize(n0 + n1 + n2 + n3);
			vbit++;
		}

		vbit = model_vb->begin();
		// Jetzt Texturkoordinaten
		for (unsigned cur = 0; cur < model_vb->size(); ++cur)
		{
			vbit->tex() = sge::math::vector2((vbit->normal().x()+1)/2,(vbit->normal().z()+1)/2);
			vbit++;

			/*
			sge::math::vector3 a,b;

			

			// Vorletzter Vertex, dann den naechsten so mitnehmen
			if (cur % z_reps == z_reps - 1)
			{
				a = sge::math::vector3(0,-1,0);
				b = sge::math::vector3((*model_vb)[(cur + z_reps) % model_vb->size()].pos() - (*model_vb)[cur].pos());
			}
			else
			{
				a = sge::math::vector3((*model_vb)[cur+1].pos() - (*model_vb)[cur].pos());
				b = sge::math::vector3((*model_vb)[(cur+1+z_reps) % model_vb->size()].pos() - (*model_vb)[cur].pos());
			}

			sge::math::vector3 n = sge::math::normalize(cross(a,b));
			//std::cout << "a: " << a << ", b: " << b << "\n";

			vbit->tex() = sge::math::vector2((n.x()+1)/2,(n.z()+1)/2);
			//vbit->tex() = sge::math::vector2(std::asin(n.x())/sge::math::PI*0.5,std::asin(n.y())/sge::math::PI*0.5);

			if ((cur % z_reps) <= 1)
				//std::cout << "cur(" << cur << "),pos("<< (*model_vb)[cur].pos() <<"),n(" << n << "),cur+1("<<(*model_vb)[cur+1].pos()<<"),cur+1+z_reps("<<(*model_vb)[(cur+1+z_reps)%model_vb->size()].pos()<<")\n";
				std::cout << "cur=" << cur << ",a" << a << ",b" << b << ",n" << n << ",vbit->tex()" << vbit->tex() << "\n";
			vbit++;
		*/
		}
	}


	const unsigned triangle_count = ((z_reps-1) * 2 - 1) * y_reps;
	const sge::index_buffer_ptr model_ib = rend->create_index_buffer(triangle_count * 3);
	{
		sge::lock_ptr<sge::index_buffer_ptr> _lock(model_ib);
		sge::index_buffer::iterator ibit = model_ib->begin();

		unsigned cur = 0;
		for (unsigned y = 0; y < y_reps; ++y)
		{
			// Oberstes Dreieck. Die Z-Schritte gehen von senkrecht nach oben bis zur Horizontalen, also im Uhrzeigersinn
			*ibit++ = cur;
			*ibit++ = cur+1;
			// "gegenueber"
			*ibit++ = (cur+1+z_reps)%model_vb->size();

			cur++;

			// Alle weiteren Dreiecke
			for (unsigned z = 0; z < z_reps-2; ++z)
			{
				// Erstes Dreieck
				*ibit++ = cur;
				*ibit++ = cur+1;
				*ibit++ = (cur+1+z_reps)%model_vb->size();

				*ibit++ = (cur+1+z_reps)%model_vb->size();
				*ibit++ = (cur+z_reps)%model_vb->size();
				*ibit++ = cur;

				cur++;
			}

			cur++;
		}
	}

	bool running = true;

	const sge::image_ptr grass_image = image_loader->load_image(sge::media_path() + "grass.png");
	sge::texture_ptr tex = rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::point_filter);
	rend->set_texture(tex);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer,true);
	rend->set_bool_state(sge::bool_state::enable_culling,true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer,true);
	rend->set_cull_mode(sge::cull_mode::back);
	rend->set_float_state(sge::float_state::zbuffer_clear_val,0);
	rend->set_depth_func(sge::depth_func::greater);

	sge::math::vector3 translation(0,-r * 2.0/3.0,0);
	sge::space_unit fovy_deg = 45,fovy_rad = fovy_deg * sge::math::PI / 180,near = 1,far = 100,rot = 0;
	sge::space_unit aspect = static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height();
	sge::space_unit rotation_xz(0),rotation_xy(0);

	sge::timer press_timer(500);
	while (running)
	{
		rend->begin_rendering();
		sge::window::dispatch();
		is->dispatch();

		translation.x() += ks[sge::KC_LEFT] * 0.01;
		translation.x() -= ks[sge::KC_RIGHT] * 0.01;
		translation.y() -= ks[sge::KC_UP] * 0.01;
		translation.y() += ks[sge::KC_DOWN] * 0.01;
		translation.z() += ks['w'] * 0.01;
		translation.z() -= ks['s'] * 0.01;

		static sge::key_state last_x = 0, last_y = 0;
		if (ks[sge::KC_MOUSEX] != last_x)
		{
			rotation_xz += ks[sge::KC_MOUSEX];
			last_x = ks[sge::KC_MOUSEX];
		}
		if (ks[sge::KC_MOUSEY] != last_y)
		{
			rotation_xy += ks[sge::KC_MOUSEY];
			last_y = ks[sge::KC_MOUSEY];
		}

	//	sge::space_unit aspect = static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height();
		// Alte Formel ohne 2* (anscheinend falsch)
		//sge::space_unit fovy_rad = fovy_deg*sge::math::PI/180,hnear = 2*std::tan(fovy_rad/2)*near,wnear = hnear * aspect,fovx_rad = 2*std::atan((wnear/2)/near);
		//sge::space_unit fovy_rad = fovy_deg*sge::math::PI/180,hnear = 2*std::tan(fovy_rad/2)*near,wnear = 2 * hnear * aspect,fovx_rad = 2*std::atan((wnear/2)/near);


	//	rend->transform(sge::math::matrix_translation(translation) * sge::math::matrix_rotation_y(-rotation_xz) * sge::math::matrix_rotation_x(rotation_xy));
		rend->transform(sge::math::matrix_translation(translation) * sge::math::matrix_rotation_y(-rotation_xz) * sge::math::matrix_rotation_x(rotation_xy));
		// Projektionsmatrix setzen
		rend->projection(sge::math::matrix_perspective(aspect,fovy_rad,near,far));
	//	rend->projection(matrix_perspective(static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));
//		rend->projection(matrix_perspective(static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::space_matrix perspect = 
	//				sge::math::transpose(sge::math::matrix_perspective(static_cast../../src::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::vector3 nl(perspect[0][3]+perspect[0][0],perspect[1][3]+perspect[1][0],perspect[2][3]+perspect[2][0]);
	//	std::cout << "left normal: " << nl.normalize() << "\n";
		rend->set_texture(tex);
		rend->render(model_vb,model_ib,0,model_vb->size(),sge::indexed_primitive_type::triangle,triangle_count,0);
		//rend->set_texture(sge::shared_ptr<sge::texture>());
		//rend->render(model_vb,0,model_vb->size(),sge::nonindexed_primitive_type::point);

		// Hier Programmlogik
		if (ks[sge::KC_ESC])
			running = false;

		rend->end_rendering();
	}
}
