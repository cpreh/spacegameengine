#include "../core/main/plugin_manager.hpp"
#include "../core/renderer/lock_ptr.hpp"
#include "../core/main/util.hpp"
#include "../core/sprite/system.hpp"
#include "../core/sprite/sprite.hpp"
#include "../core/renderer/font.hpp"
#include "../core/renderer/renderer.hpp"
#include "../core/renderer/renderer_types.hpp"
#include "../gui/manager.hpp"
#include "../gui/button.hpp"
#include "../gui/text_edit.hpp"
#include "../gui/list.hpp"
#include "../gui/icon_button.hpp"
#include "../gui/frame.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

class input_receiver {
public:
	input_receiver(bool& running)
		: running(running) {}
	void operator()(const sge::key_pair& p)
	{
		if(p.first.code == sge::KC_ESC)
			running = false;
	}
private:
	bool& running;
};

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
//	sge::sprite_system ss(rend);
//	sge::image_ptr im = pl->load_image("/home/sefi/cpp/spacegame/mainskin/cancel_0.png");
//	const std::string bender_name("bender");

//	ss.add_texture(im,bender_name);
//	ss.add_texture(im,":(((");
//	sge::sprite spr(ss,sge::point(0,0),sge::dim(0.5,0.5),0,bender_name);
//	sge::sprite spr2(ss,sge::point(0.5,0.5),sge::dim(0.5,0.5),0,bender_name);
	sge::gui::manager man(rend,is,fn,pl,"/home/sefi/cpp/spacegame/mainskin/");
	sge::gui::frame fr1(man,0,sge::point(0,0),sge::dim(1,1),"cancel_0");
	sge::gui::button btn1(man,&fr1,"Beenden!",sge::point(0,0.1),sge::dim(0.5,0.5));
	sge::gui::list list1(man,&fr1,sge::point(0.5,0.1),sge::dim(0.2,0.8));
	sge::gui::icon_button icbtn1(man,&fr1,sge::point(0,0.8),sge::dim(0.5,0.1),"newgame_0","newgame_1","newgame_2");
	//sge::gui::text_edit te1(man,0,sge::point(0,0.5),sge::dim(0.5,0.3),"abc");
	//sge::gui::icon_button ib1(man,0,sge::point(0.5,0),sge::dim(0.5,0.5),"exit_0","exit_1","exit_2");
	list1.push_back("LOL");
	list1.push_back("BAR");
	list1.push_back("ROFL!");
	for(int i = 0; i < 20; ++i)
		list1.push_back("TEST");

	btn1.click_signal.connect(boost::lambda::var(running) = false);
	
	input_receiver recv(running);
	sge::callback_handle cbh = is->register_callback(recv);

	fn.height(0.05);

	while(running)
	{
		rend->begin_rendering();
		is->dispatch();
//		ss.draw();
		man.process();
		fn.draw_text("1234567890 abcdef ghij adsfasdf asf asdds klmn 1234567890",sge::point(0.1,0.1),sge::dim(0.8,0.8),sge::colors::white);
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
