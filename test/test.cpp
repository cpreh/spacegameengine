/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <cstdlib>
#include <exception>
#include <ostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/font/font.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/types.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/image_view_hack.hpp>
#include <sge/renderer/image_view_factory.hpp>
#include <sge/media.hpp>
#include <sge/input/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/endianness.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/scoped_connection.hpp>
#include <sge/iostream.hpp>
#include <sge/math/basic_sequence_impl.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/vector_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/sprite/intrusive_system.hpp>
#include <sge/log/macros.hpp>
#include <sge/log/global.hpp>
#include <sge/log/temporary_output.hpp>
#include <sge/log/logger.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <sge/renderer/color.hpp>
#include <sge/bitfield.hpp>
#include <sge/bitfield_impl.hpp>

enum testenum {
	foo,
	bar,
	esize
};

template class sge::bitfield<testenum, esize>;

int main()
try
{
	typedef sge::bitfield<testenum, esize> myfield;
	myfield testfield;
	testfield |= foo;
	*testfield.begin() = true;

	//sge::log::logger &log(sge::log::global());

	//log.activate(sge::log::level::debug);

	sge::log::logger inner_logger(sge::log::global(), SGE_TEXT("inner: "));

	inner_logger.activate(sge::log::level::warning);

	//sge::cout << inner_logger.formatter()->format(SGE_TEXT("BLAH"));

	//SGE_LOG_DEBUG(log, sge::log::_1 << SGE_TEXT("HAHA"));

	SGE_LOG_WARNING(inner_logger, sge::log::_1 << SGE_TEXT("blubb"));

	bool running = true;
	sge::plugin::manager pm;

	const sge::plugin::plugin<sge::renderer::system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer::system>().load();
	const sge::plugin::plugin<sge::input::system>::ptr_type input_plugin = pm.get_plugin<sge::input::system>().load();

	const sge::renderer::system_ptr rs(renderer_plugin->get()());
	const sge::renderer::parameters param(sge::renderer::display_mode(1280,1024,sge::renderer::bit_depth::depth32,100), true);
	const sge::renderer::device_ptr rend = rs->create_renderer(param);

	const sge::input::system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin::plugin<sge::font::system>::ptr_type font_plugin = pm.get_plugin<sge::font::system>().load();
	const sge::font::system_ptr fs(font_plugin->get()());

	const sge::font::metrics_ptr metrics = fs->create_font(sge::media_path() / SGE_TEXT("fonts/default.ttf"), 15);
	const sge::font::drawer_ptr fn_drawer(new sge::font::drawer_3d(rend));

	sge::font::font fn(metrics, fn_drawer);

	const sge::plugin::plugin<sge::image::loader>::ptr_type image_plugin = pm.get_plugin<sge::image::loader>().load();
	const sge::image::loader_ptr image_loader(image_plugin->get()());

	sge::sprite::intrusive_system sys(rend);
	sge::sprite::intrusive_object spr(sys, 1);
	sge::sprite::intrusive_object spr2(spr);

	using boost::lambda::var;
	using boost::lambda::bind;
//	using boost::lambda::_1;
	using boost::lambda::if_;

	const sge::scoped_connection cb(
		is->register_callback(
			if_(
				bind(
					&sge::input::key_type::code,
					bind(
						&sge::input::key_pair::key,
						boost::lambda::_1))
					== sge::input::kc::key_escape)
				[var(running)=false]));

	/*sge::renderer::texture_ptr const testtex(
		rend->create_texture(
			sge::renderer::texture::dim_type(256, 256),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::readable));*/
	sge::renderer::texture_ptr const testtex(
		sge::image::create_texture(
			sge::media_path() / SGE_TEXT("grass.png"),
			rend,
			image_loader,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::readable));

	{
		sge::renderer::scoped_texture_lock const lock_(
			sge::renderer::make_scoped_lock(
				testtex,
				sge::renderer::lock_rect(
					100,
					100,
					200,
					200),
				sge::renderer::lock_flags::readwrite));

		boost::gil::fill_pixels(
			sge::renderer::subimage_view(
				lock_.value(),
				sge::renderer::lock_rect(0, 0, 50, 50)),
			sge::renderer::make_color_rgba(255, 0, 0, 255));


		image_loader->create_image(
			sge::renderer::make_const_view(lock_.value()))->save(
				SGE_TEXT("./sge_test.png"));
	}

/*	rend->set_state(
		sge::renderer::state_list
			(sge::renderer::color_state::clear_color = sge::renderer::color(255, 255, 255, 255))
			(sge::renderer::bool_state::clear_backbuffer = true)
			(sge::renderer::depth_func::off)
			(sge::renderer::cull_mode::off));*/
	//const sge::string some_text(SGE_TEXT("abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb"));
	const sge::string some_text(SGE_TEXT("de\nEFygY\ngyhgh"));
	while(running)
	{
		const sge::renderer::scoped_block block_(rend);

		rend->get_window()->dispatch();
		is->dispatch();

		fn.draw_text(some_text, sge::font::pos(100,100), sge::font::dim(100,500), sge::font::align_h::right, sge::font::align_v::bottom);
	}
	return EXIT_SUCCESS;
}
catch(const sge::exception& e)
{
	sge::cerr << "Program terminated (sge::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(const std::exception& e)
{
	sge::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	sge::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}
