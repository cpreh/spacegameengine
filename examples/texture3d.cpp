/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/exception.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/volume_texture.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/config/media_path.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/scoped.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/shader/variable.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/shader/sampler.hpp>
#include <sge/image3d/view/optional_pitch.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image3d/view/make_const.hpp>
#include <sge/image3d/view/format.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/make.hpp>
#include <sge/shader/vf_to_string.hpp>
#include <sge/camera/projection/perspective.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/filter/point.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/math/dim/input.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/exception.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <streambuf>
#include <cstddef>

namespace
{
namespace vf
{
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(position)
}

typedef 
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector
	<
		sge::renderer::scalar,
		3
	>,
	tags::position
> 
position;

typedef 
sge::renderer::vf::format
<
	boost::mpl::vector1
	<
		position
	>
> 
format;

typedef 
sge::renderer::vf::view
<
	format
>
vertex_view;
}

sge::renderer::vertex_buffer_ptr const
create_cube(
	sge::renderer::device_ptr const renderer,
	sge::shader::object &sh,
	sge::renderer::size_type const slices)
{
	sge::shader::scoped scoped_shader(
		sh);

	sge::renderer::vertex_buffer_ptr const vb = 
		renderer->create_vertex_buffer(
			sge::renderer::vf::dynamic::make_format<vf::format>(),
			// Two triangles per slice
			static_cast<sge::renderer::size_type>(
				6 * slices),
			sge::renderer::resource_flags::none);

	sge::renderer::scoped_vertex_lock const vblock(
		vb,
		sge::renderer::lock_mode::writeonly);

	vf::vertex_view const vertices(
		vblock.value());

	vf::vertex_view::iterator vb_it(
		vertices.begin());

	typedef 
	vf::position::packed_type 
	position_vector;

	for (sge::renderer::size_type i = 0; i < slices; ++i)
	{
		sge::renderer::scalar const z = 
			1.0f - static_cast<sge::renderer::scalar>(i)/static_cast<sge::renderer::scalar>(slices);
		// left top
		(*vb_it++).set<vf::position>(
			position_vector(
				0,1,z));
		// left bottom
		(*vb_it++).set<vf::position>(
			position_vector(
				0,0,z));
		// right top
		(*vb_it++).set<vf::position>(
			position_vector(
				1,1,z));
		// right top
		(*vb_it++).set<vf::position>(
			position_vector(
				1,1,z));
		// left bottom
		(*vb_it++).set<vf::position>(
			position_vector(
				0,0,z));
		// right bottom
		(*vb_it++).set<vf::position>(
			position_vector(
				1,0,z));
	}

	return vb;
}

class texture3d
{
public:
	explicit
	texture3d(
		fcppt::filesystem::path const &directory,
		fcppt::string const &prefix,
		std::size_t const slice_size,
		std::size_t const slices);

	sge::image3d::view::const_object const
	view() const;
private:
	typedef
	fcppt::container::raw_vector<unsigned char> 
	byte_vector;

	byte_vector bytes_;
	std::size_t slice_size_,slices_;
};

texture3d::texture3d(
	fcppt::filesystem::path const &directory,
	fcppt::string const &prefix,
	std::size_t const _slice_size,
	std::size_t const _slices)
:
	bytes_(
		static_cast<byte_vector::size_type>(
			_slices * _slice_size * _slice_size)),
	slice_size_(
		_slice_size),
	slices_(
		_slices)
{
	byte_vector::iterator current_byte = 
		bytes_.begin();

	for (std::size_t current_slice = 1; current_slice <= _slices; ++current_slice)
	{
		fcppt::filesystem::path const p = 
			directory / (prefix + FCPPT_TEXT(".") + boost::lexical_cast<fcppt::string>(current_slice));

		fcppt::io::cifstream file(
			p);

		if (!file.is_open())
			throw 
				fcppt::exception(
					FCPPT_TEXT("Couldn't open file ")+
					p.string());

		std::string const file_content(
			(std::istreambuf_iterator<char>(
				file)),
			std::istreambuf_iterator<char>());

		FCPPT_ASSERT(
			file_content.size() % 2u == 0);

		for (std::string::size_type current_texel = 0; current_texel < file_content.size(); current_texel += 2)
			*current_byte++ = 
				static_cast<byte_vector::value_type>(
					static_cast<double>(file_content[current_texel+1] << 8 | file_content[current_texel])/65536.0 * 255.0);
	}
}

sge::image3d::view::const_object const
texture3d::view() const
{
	return 
		sge::image3d::view::make_const(
			reinterpret_cast<sge::image::const_raw_pointer>(
				bytes_.data()),
			sge::image3d::dim(
				slice_size_,
				slice_size_,
				slices_),
			sge::image::color::format::gray8,
			sge::image3d::view::optional_pitch());
}
}

int 
main(
	int argc,
	char*argv[])
try
{
	boost::program_options::options_description desc(
		"To use this sge example, you need a 3D texture somewhere on your file system.\n"
		"The texture must consist of one file per slice and all slice files\n"
		"have to be in the same directory.\n"
		"You can specify said directory with \"directory\". The file names have the\n"
		"format \"prefix.number\" where prefix can be specified via the \"prefix\"\n"
		"option. The numbers start with 1.\n"
		"The slice files themselves consist of 16 bit integers in little endian.\n"
		"No header. Sample images can be found at\n\n"
		"http://www-graphics.stanford.edu/data/voldata/\n\nOther options include");
	desc.add_options()
    ("help", "Produce help message")
    ("directory", boost::program_options::value<fcppt::string>(), "Set the directory where to take the slices from (see above)")
    ("prefix", boost::program_options::value<fcppt::string>(), "Slice prefix (see above)")
    ("slice-count", boost::program_options::value<std::size_t>(), "How many slices are there")
    ("slice-size", boost::program_options::value<std::size_t>(), "How big is one slice")
    ("screen-size", boost::program_options::value<sge::renderer::screen_size>()->default_value(sge::renderer::screen_size(1024,768)), "Screen resolution, format: (x,y)");

	boost::program_options::variables_map vm;
	boost::program_options::store(
		boost::program_options::parse_command_line(
			argc, 
			argv, 
			desc), 
		vm);
	boost::program_options::notify(
		vm);    

	if (vm.count("help")) 
	{
		std::cout << desc << "\n";
		return EXIT_SUCCESS;
	}

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge test for 3d textures")
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						vm["screen-size"].as<sge::renderer::screen_size>(),
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_buffer::d24,
					sge::renderer::stencil_buffer::off,
					sge::renderer::window_mode::windowed,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::manage_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector
			)
		)
	);

	sge::renderer::device_ptr const rend(
		sys.renderer());

	texture3d mytex(
		vm["directory"].as<fcppt::string>(),
		vm["prefix"].as<fcppt::string>(),
		vm["slice-size"].as<std::size_t>(),
		vm["slice-count"].as<std::size_t>());

	sge::shader::object shader(
		rend,
		sge::config::media_path()
			/ FCPPT_TEXT("shaders")
			/ FCPPT_TEXT("texture3d_vertex.glsl"),
		sge::config::media_path()
			/ FCPPT_TEXT("shaders")
			/ FCPPT_TEXT("texture3d_fragment.glsl"),
		sge::shader::vf_to_string<vf::format>(),
		fcppt::assign::make_container<sge::shader::variable_sequence>
			(sge::shader::variable(
				"mvp",
				sge::shader::variable_type::uniform,
				sge::renderer::matrix4()))
			/*
			(sge::shader::variable(
				"mv",
				sge::shader::variable_type::uniform,
				sge::renderer::matrix4()))*/,
		fcppt::assign::make_container<sge::shader::sampler_sequence>
			(sge::shader::sampler(
				"tex",
				rend->create_volume_texture(
					mytex.view(),
					sge::renderer::filter::linear,
					sge::renderer::resource_flags::none),
				3)));

	sge::renderer::vertex_buffer_ptr const vb = 
		create_cube(
			rend,
			shader,
			109);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::clear_zbuffer = true)
			(sge::renderer::state::bool_::enable_alpha_blending = true)
			(sge::renderer::state::source_blend_func::src_alpha)
			(sge::renderer::state::dest_blend_func::inv_src_alpha)
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::float_::zbuffer_clear_val = 1.f)
			(sge::renderer::state::color::clear_color = sge::image::colors::black()));

	sge::renderer::scoped_vertex_buffer const vb_context(
		rend,
		vb);

	sge::camera::object cam(
		sge::camera::parameters(
			sge::camera::projection::perspective(
				sge::renderer::aspect<sge::renderer::scalar>(
					rend->screen_size()),
				fcppt::math::deg_to_rad(
					static_cast<sge::renderer::scalar>(
						90)),
				static_cast<sge::renderer::scalar>(
					0.1),
				static_cast<sge::renderer::scalar>(
					10)),
			static_cast<sge::renderer::scalar>(
				0.2),
			static_cast<sge::renderer::scalar>(
				200.0),
			sge::renderer::vector3::null(),
			*sys.keyboard_collector(),
			*sys.mouse_collector()));

	sge::time::timer frame_timer(
		sge::time::second(
			1));

	while(running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(rend);

		sge::shader::scoped scoped_shader(
			shader);

		rend->render(
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(vb->size()),
			sge::renderer::nonindexed_primitive_type::triangle);

		cam.update(
			static_cast<sge::renderer::scalar>(
				frame_timer.reset()));

		shader.set_uniform(
			"mvp",
			cam.mvp());

		/*
		shader.set_uniform(
			"mv",
			cam.world());
		*/
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT("\n");
}
catch(std::exception const &e)
{
	std::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
