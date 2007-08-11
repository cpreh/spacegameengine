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
#include <sge/renderer/screenshot.hpp>
#include <ctime>
#include <cstdlib>

#include "skydome.hpp"

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

	bool running = true;

	const sge::image_ptr cloud_image = image_loader->load_image(sge::media_path() + "cloudsquare.jpg");
	sge::texture_ptr tex = rend->create_texture(cloud_image->data(), cloud_image->width(), cloud_image->height(), sge::linear_filter);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer,true);
	rend->set_bool_state(sge::bool_state::enable_culling,true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer,true);
	rend->set_cull_mode(sge::cull_mode::back);
	rend->set_float_state(sge::float_state::zbuffer_clear_val,0);
	rend->set_depth_func(sge::depth_func::greater);

	skydome sky(3,16,8,rend,tex);

	sge::math::vector3 translation(0,0,0);
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
		//rend->set_texture(tex);
		//rend->render(model_vb,model_ib,0,model_vb->size(),sge::indexed_primitive_type::triangle,triangle_count,0);
		sky.draw();
		//rend->set_texture(sge::shared_ptr<sge::texture>());
		//rend->render(model_vb,0,model_vb->size(),sge::nonindexed_primitive_type::point);

		// Hier Programmlogik
		if (ks[sge::KC_ESC])
			running = false;

		rend->end_rendering();
		if (ks[sge::KC_F12])
			sge::screenshot(rend,image_loader,"screenie.png");
	}
}
