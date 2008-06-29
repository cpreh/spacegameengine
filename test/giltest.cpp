#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/iostream.hpp>
#include <sge/exception.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_state.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/foreach.hpp>
#include <boost/array.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(1024, 768);
	
	const sge::renderer::device_ptr rend = sys.renderer;

	const sge::renderer::vertex_buffer_ptr vb(rend->create_vertex_buffer(
		sge::renderer::const_vertex_view(
			0,
			3,
			sge::renderer::vertex_format()
				.add(sge::renderer::vertex_usage::pos)
				.add(sge::renderer::vertex_usage::tex))));
	{
		const sge::renderer::scoped_lock<sge::renderer::vertex_buffer_ptr> lock_(
			sge::renderer::make_scoped_lock(
				vb,
				sge::renderer::lock_flags::writeonly));
		sge::renderer::vertex_view v(vb->view());
		sge::renderer::vertex_view::iterator it(v.begin());
		(it  )->tex() = sge::renderer::tex_pos(0, 0);
		(it++)->pos() = sge::renderer::pos3(-1, 1, 0);
		(it  )->tex() = sge::renderer::tex_pos(1, 0);
		(it++)->pos() = sge::renderer::pos3(1, 0, 0);
		(it  )->tex() = sge::renderer::tex_pos(0, 1);
		(it  )->pos() = sge::renderer::pos3(-1, -1, 0);
	}

	const boost::array<sge::uint16, 3> indices = {
		{ 0, 1, 2 }
		};

	const sge::renderer::index_buffer_ptr ib(
		rend->create_index_buffer(
			sge::renderer::const_dynamic_index_view(
				sge::renderer::const_index_view_16(
					indices.data(),
					indices.size()))));

	typedef boost::array<sge::uint32, 10 * 10> tex_data_type;
	tex_data_type tex_data;
	BOOST_FOREACH(sge::uint32 &pixel, tex_data)
		pixel = (255 << 24) | (255 << 16) | (255 << 8) | 255;

	const sge::renderer::texture_ptr tex(
		rend->create_texture(
			sge::renderer::const_image_view(
				boost::gil::interleaved_view(
					10,
					10,
					reinterpret_cast<sge::renderer::rgba8_pixel const*>(
						tex_data.data()),
					10 * 4)),
				sge::renderer::linear_filter));
	rend->set_texture(tex);

	while(true)
	{
		const sge::renderer::scoped_block block_(rend);
		
		const sge::renderer::scoped_state state_(
			rend,
			sge::renderer::state_list
			//	(sge::renderer::bool_state::enable_lighting = false)
				(sge::renderer::bool_state::enable_alpha_blending = true)
				(sge::renderer::source_blend_func::src_alpha)
				(sge::renderer::dest_blend_func::inv_src_alpha)
			//	(sge::renderer::cull_mode::off)
			//	(sge::renderer::depth_func::off)
			//	(sge::renderer::stencil_func::off)
			//	(sge::renderer::draw_mode::fill)
		);

		rend->render(
			vb,
			ib,
			0,
			3,
			sge::renderer::indexed_primitive_type::triangle,
			1,
			0);
	}
}
catch(const sge::exception& e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(const std::exception& e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
