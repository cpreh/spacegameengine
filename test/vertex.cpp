#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/window.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/math/vector.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

#include <sge/renderer/vf/unspecified.hpp>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input));

	typedef sge::renderer::vf::pos<
		float,
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
		sys.renderer());
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
		
		typedef pos3_type::packed_type vec3;

		(*vb_it).set<pos3_type>(vec3(-1.f, 1.f, 0.f));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 255, 255));
		(*vb_it).set<pos3_type>(vec3(-1.f, -1.f, 0.f));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 0, 255));
		(*vb_it).set<pos3_type>(vec3(1.f, 1.f, 0.f));
		(*vb_it++).set<color_type>(sge::renderer::rgba8_color(255, 255, 255, 255));
	}

	bool running = true;

	sge::input::system_ptr const is = sys.input_system();

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	sge::signals::scoped_connection const cb(
		is->register_callback(
			if_(bind(&sge::input::key_type::code,
				bind(&sge::input::key_pair::key,boost::lambda::_1))
			== sge::input::kc::key_escape)
		[var(running)=false])
	);

	rend->set_state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::colors::black()));
	
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
