#include "../core/main/plugin_manager.hpp"
#include "../core/renderer/lock_ptr.hpp"
#include "../core/main/util.hpp"
#include "../core/renderer/sprite_system.hpp"
#include "../core/renderer/font.hpp"
#include "../core/renderer/renderer.hpp"
#include "../core/renderer/renderer_types.hpp"
#include "../core/input/input_functions.hpp"
#include "../gui/manager.hpp"
#include "../gui/button.hpp"
#include "../gui/text_edit.hpp"
#include "../gui/list.hpp"
#include "../gui/icon_button.hpp"
#include "../gui/frame.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

int main()
try
{
	bool running = true;
	sge::plugin_manager pm;
	sge::renderer_system_ptr rs = pm.get_plugin<sge::renderer_system>();
	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::BD_32,100));
	sge::renderer_ptr rend = rs->create_renderer(param);
	sge::image_loader_ptr pl = pm.get_plugin<sge::image_loader>();
	sge::font_system_ptr fs = pm.get_plugin<sge::font_system>();
	sge::input_system_ptr is = pm.get_plugin<sge::input_system>(rend->get_window());
	sge::font fn(rend,fs,"/usr/share/fonts/corefonts/arial.ttf");
	//sge::sprite_system ss(rend);
	sge::image_ptr im = pl->load_image("/home/sefi/cpp/spacegame/mainskin/button.png");
	const std::string bender_name("bender");
	//ss.add_texture(im,bender_name);
	//sge::sprite spr(ss,sge::point(0.5,0.5),sge::dim(0.5,0.5),0,bender_name);
	//sge::sprite spr2(ss,sge::point(0,0),sge::dim(0.5,0.5),0,bender_name);
	sge::gui::manager man(rend,fn,pl,"/home/sefi/cpp/spacegame/mainskin/");
	sge::gui::frame fr1(man,0,sge::point(0,0.2),sge::dim(1,1),"cancel_0");
	sge::gui::button btn1(man,&fr1,"Beenden!",sge::point(0,0.1),sge::dim(0.5,0.5));
	//sge::gui::list list1(man,&fr1,sge::point(0.5,0),sge::dim(0.2,0.2));
//	sge::gui::icon_button icbtn1(man,&fr1,sge::point(0,0),sge::dim(0.1,0.1),"newgame_0","newgame_1","newgame_2");
	//sge::gui::text_edit te1(man,0,sge::point(0,0.5),sge::dim(0.5,0.3),"abc");
	//sge::gui::icon_button ib1(man,0,sge::point(0.5,0),sge::dim(0.5,0.5),"exit_0","exit_1","exit_2");
	//list1.push_back("LOL");
	//list1.push_back("BAR");
	//list1.push_back("ROFL!");

	btn1.click_signal.connect(boost::lambda::var(running) = false);
	
	while(running)
	{
		const sge::input_array inp = is->get_input();
		if(sge::key_value(inp,sge::KC_ESC))
			running = false;
		rend->begin_rendering();
		//ss.draw();
		man.process(inp);
		fn.draw_text("abc",sge::point(0.5,0.5),sge::dim(0.5,0.5),sge::colors::black);
		rend->end_rendering();
	}
}
catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return -1;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return -1;
}
