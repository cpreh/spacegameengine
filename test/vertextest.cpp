#include <sge/init.hpp>
#include <sge/systems.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/su.hpp>
#include <sge/scoped_connection.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/input/system.hpp>
#include <sge/math/vector.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(
		sge::renderer::screen_size_t(1024, 768));
	sys.init<sge::init::input>();

	typedef sge::renderer::vf::pos<
		sge::space_unit,
		3
	> pos3_type;

	typedef sge::renderer::vf::color<
		sge::renderer::rgba8_color
	> color_type;

	typedef sge::renderer::vf::format<
		boost::mpl::vector<
			pos3_type,
			color_type
		>
	> format;

	sge::renderer::device_ptr const rend(
		sys.renderer);
	sge::renderer::vertex_buffer_ptr const vb(
		rend->create_vertex_buffer(
			sge::renderer::vf::make_dynamic_format<format>(),
			3,
			sge::renderer::resource_flags::none));

	{
		sge::renderer::scoped_vertex_lock const vblock(
			sge::renderer::make_scoped_lock(
				vb,
				sge::renderer::lock_flags::writeonly));

		typedef sge::renderer::vf::view<
			format
		> vertex_view;
		
		vertex_view const vertices(
			vblock.value());

		vertex_view::iterator vb_it = vertices.begin();
		
		(*vb_it).set<pos3_type, 0>(sge::math::vector3(-1, 1, 0));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 255, 255));
		(*vb_it).set<pos3_type>(sge::math::vector3(-1, -1, 0));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 0, 255));
		(*vb_it).set<pos3_type>(sge::math::vector3(1, 1, 0));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 255, 255));
	}

	bool running = true;

	sge::input::system_ptr const is = sys.input_system;

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	sge::scoped_connection const cb(
		is->register_callback(
			if_(bind(&sge::input::key_type::code,
				bind(&sge::input::key_pair::key,boost::lambda::_1))
			== sge::input::kc::key_escape)
		[var(running)=false])
	);
	
	while(running)
	{
		sge::renderer::scoped_block const block_(rend);
		sge::window::dispatch();
		is->dispatch();

		rend->render(
			vb,
			0,
			3,
			sge::renderer::nonindexed_primitive_type::triangle_strip);
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
