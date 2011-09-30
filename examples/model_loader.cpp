/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/all_extensions.hpp>
#include <sge/camera/duration.hpp>
#include <sge/camera/movement_speed.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/camera/rotation_speed.hpp>
#include <sge/exception.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/log/global.hpp>
#include <sge/model/obj/create.hpp>
#include <sge/model/obj/face.hpp>
#include <sge/model/obj/face_point.hpp>
#include <sge/model/obj/face_point_sequence.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/instance_ptr.hpp>
#include <sge/model/obj/loader.hpp>
#include <sge/model/obj/loader_ptr.hpp>
#include <sge/model/obj/mesh.hpp>
#include <sge/model/obj/mesh_sequence.hpp>
#include <sge/model/obj/normal.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/vb_converter/convert.hpp>
#include <sge/model/obj/vb_converter/roles/normal.hpp>
#include <sge/model/obj/vb_converter/roles/position.hpp>
#include <sge/model/obj/vb_converter/roles/texcoord.hpp>
#include <sge/model/obj/vertex.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/config/create_command_line_parameters.hpp>
#include <sge/parse/json/config/merge_command_line_parameters.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_string_exn.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/const_scoped_vertex_lock.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/light/attenuation.hpp>
#include <sge/renderer/light/constant_attenuation.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/linear_attenuation.hpp>
#include <sge/renderer/light/object.hpp>
#include <sge/renderer/light/point.hpp>
#include <sge/renderer/light/position.hpp>
#include <sge/renderer/light/quadratic_attenuation.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vf/const_tag.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/homogenous_pair.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>

#include <boost/mpl/map/map10.hpp>
#include <boost/mpl/pair.hpp>
#include <fcppt/config/external_end.hpp>
#include <fcppt/mpl/index_of.hpp>

namespace
{
// Define the vertex format which consists of a position value and a normal (for the diffuse shading)
namespace vf
{
// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::pos<sge::renderer::scalar,3>
position;

typedef
sge::renderer::vf::texpos<sge::renderer::scalar, 2>
texcoord;

// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::normal<sge::renderer::scalar>
normal;

typedef
sge::renderer::vf::part
<
	boost::mpl::vector3<position,texcoord,normal>
>
format_part;

typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<format_part>
>
format;
}

class compiled_model
{
FCPPT_NONCOPYABLE(
	compiled_model);
public:
	explicit
	compiled_model(
		sge::model::obj::instance const &,
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &,
		sge::renderer::texture::planar_ptr);

	void
	render();

	sge::renderer::vertex_buffer const &
	vb() const;

	~compiled_model();
private:
	sge::renderer::vertex_declaration const &vd_;
	sge::renderer::vertex_buffer_ptr vb_;
	sge::renderer::texture::planar_ptr texture_;
	sge::renderer::device &renderer_;
};

typedef
boost::mpl::map1
<
	boost::mpl::pair
	<
		sge::model::obj::vb_converter::roles::position,
		fcppt::mpl::index_of
		<
			vf::format_part::elements,
			vf::position
		>
	>
>
base_format;

typedef
boost::mpl::insert
<
	base_format,
	boost::mpl::pair
	<
		sge::model::obj::vb_converter::roles::texcoord,
		fcppt::mpl::index_of
		<
			vf::format_part::elements,
			vf::texcoord
		>
	>
>::type
texcoord_format;

typedef
boost::mpl::insert
<
	texcoord_format,
	boost::mpl::pair
	<
		sge::model::obj::vb_converter::roles::normal,
		fcppt::mpl::index_of
		<
			vf::format_part::elements,
			vf::normal
		>
	>
>::type
texcoord_normal_format;

typedef
boost::mpl::insert
<
	base_format,
	boost::mpl::pair
	<
		sge::model::obj::vb_converter::roles::normal,
		fcppt::mpl::index_of
		<
			vf::format_part::elements,
			vf::normal
		>
	>
>::type
normal_format;

sge::renderer::vertex_buffer_ptr const
choose_format_and_convert(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::model::obj::instance const &_model,
	sge::renderer::texture::planar_ptr const _texture)
{
	if(_texture)
	{
		if(_model.normals().empty())
			return
				sge::model::obj::vb_converter::convert<vf::format_part,texcoord_format>(
					_renderer,
					_vd,
					sge::renderer::resource_flags::readable,
					_model);

		return
			sge::model::obj::vb_converter::convert<vf::format_part,texcoord_normal_format>(
				_renderer,
				_vd,
				sge::renderer::resource_flags::readable,
				_model);
	}

	if(!_model.normals().empty())
		return
			sge::model::obj::vb_converter::convert<vf::format_part,normal_format>(
				_renderer,
				_vd,
				sge::renderer::resource_flags::readable,
				_model);

	return
		sge::model::obj::vb_converter::convert<vf::format_part,base_format>(
			_renderer,
			_vd,
			sge::renderer::resource_flags::readable,
			_model);
}

compiled_model::compiled_model(
	sge::model::obj::instance const &_model,
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::renderer::texture::planar_ptr const _texture)
:
	vd_(
		_vd),
	vb_(
		choose_format_and_convert(
			_renderer,
			_vd,
			_model,
			_texture)),
	texture_(
		_texture),
	renderer_(
		_renderer)
{
}

void
compiled_model::render()
{
	fcppt::scoped_ptr<sge::renderer::texture::scoped> scoped_texture;

	if(texture_)
		scoped_texture.take(
			fcppt::make_unique_ptr<sge::renderer::texture::scoped>(
				fcppt::ref(
					renderer_),
				fcppt::cref(
					*texture_),
				sge::renderer::stage(
					0)));

	sge::renderer::scoped_vertex_declaration scoped_vd(
		renderer_,
		vd_);

	sge::renderer::scoped_vertex_buffer scoped_vb(
		renderer_,
		*vb_);

	renderer_.render_nonindexed(
		sge::renderer::first_vertex(
			0),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::nonindexed_primitive_type::triangle);
}

sge::renderer::vertex_buffer const &
compiled_model::vb() const
{
	return
		*vb_;
}

compiled_model::~compiled_model()
{
}

void
normals_to_line_drawer(
	//sge::model::obj::instance const &model,
	sge::renderer::vertex_buffer const &vb,
	sge::line_drawer::line_sequence &lines,
	sge::renderer::scalar const normal_scaling)
{
	sge::renderer::scalar const epsilon =
		0.001f;

	lines.reserve(
		static_cast<sge::line_drawer::line_sequence::size_type>(
			vb.size()));

	sge::renderer::const_scoped_vertex_lock scoped_vl(
		vb,
		sge::renderer::lock_mode::readwrite);

	typedef
	sge::renderer::vf::view<vf::format_part,sge::renderer::vf::const_tag>
	vertex_part_view;

	typedef
	vertex_part_view::iterator
	vertex_iterator;

	vertex_part_view current_vertex_view(
		scoped_vl.value());

	for(
		vertex_iterator it =
			current_vertex_view.begin();
		it != current_vertex_view.end();
		++it)
	{
		sge::renderer::vector3 const
			current_vertex =
				it->get<vf::position>(),
			current_normal =
				it->get<vf::normal>();

		FCPPT_ASSERT_ERROR(
			fcppt::math::vector::length(
				current_normal) > epsilon);

		lines.push_back(
			sge::line_drawer::line(
				current_vertex,
				current_vertex + normal_scaling * current_normal,
				sge::image::colors::red(),
				sge::image::colors::green()));
	}

#if defined(SGE_MODEL_LOADER_EXAMPLE_READ_NORMALS_FROM_FILE)
	if(model.normals().empty())
		return;

	for(
		sge::model::obj::mesh_sequence::const_iterator mesh_it =
			model.meshes().begin();
		mesh_it != model.meshes().end();
		++mesh_it)
	{
		for(
			sge::model::obj::face_sequence::const_iterator face_it =
				mesh_it->faces_.begin();
			face_it != mesh_it->faces_.end();
			++face_it)
		{
			for(
				sge::model::obj::face_point_sequence::const_iterator face_point_it =
					face_it->points_.begin();
				face_point_it != face_it->points_.end();
				++face_point_it)
			{
				sge::model::obj::vertex const current_model_vertex(
					model.vertices()[
						static_cast<sge::model::obj::vertex_sequence::size_type>(
							face_point_it->vertex_index_ - 1)]);

				FCPPT_ASSERT_PRE(
					face_point_it->normal_index_);

				sge::model::obj::normal const current_model_normal(
					model.normals()[
						static_cast<sge::model::obj::normal_sequence::size_type>(
							(*face_point_it->normal_index_)-1)]);

				sge::renderer::vector3 const
					current_vertex(
						static_cast<sge::renderer::scalar>(
							current_model_vertex.v1_),
						static_cast<sge::renderer::scalar>(
							current_model_vertex.v2_),
						static_cast<sge::renderer::scalar>(
							current_model_vertex.v3_)),
					current_normal(
						static_cast<sge::renderer::scalar>(
							current_model_normal.n1_),
						static_cast<sge::renderer::scalar>(
							current_model_normal.n2_),
						static_cast<sge::renderer::scalar>(
							current_model_normal.n3_));

				FCPPT_ASSERT_ERROR(
					fcppt::math::vector::length(
						current_normal) > epsilon);

				lines.push_back(
					sge::line_drawer::line(
						current_vertex,
						current_vertex + normal_scaling * current_normal,
						sge::image::colors::red(),
						sge::image::colors::green()));
			}
		}
	}
#endif
}
}

int
main(
	int argc,
	char *argv[])
try
{
	sge::parse::json::object const config(
		sge::parse::json::config::merge_command_line_parameters(
			sge::parse::json::parse_string_exn(
				FCPPT_TEXT("{")
				FCPPT_TEXT("\"wireframe\" : false,")
				FCPPT_TEXT("\"show-normals\" : true,")
				FCPPT_TEXT("\"normal-scaling\" : 1.0,")
				FCPPT_TEXT("\"lighting\" : true,")
				FCPPT_TEXT("\"model-file\" : \"\",")
				FCPPT_TEXT("\"texture\" : \"\",")
				FCPPT_TEXT("\"light\" : {")
					FCPPT_TEXT("\"position\" : [0.0,0.0,0.0],")
					FCPPT_TEXT("\"constant-attenuation\" : 10.0,")
					FCPPT_TEXT("\"linear-attenuation\" : 10.0,")
					FCPPT_TEXT("\"quadratic-attenuation\" : 10.0")
				FCPPT_TEXT("}")
				FCPPT_TEXT("}")),
			sge::parse::json::config::create_command_line_parameters(
				argc,
				argv)));

	fcppt::filesystem::path const
		model_file(
			sge::parse::json::find_and_convert_member<fcppt::string>(
				config,
				sge::parse::json::path(
					FCPPT_TEXT("model-file")))),
		texture_file(
			sge::parse::json::find_and_convert_member<fcppt::string>(
				config,
				sge::parse::json::path(
					FCPPT_TEXT("texture"))));

	if(
		model_file.empty()
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Please specify a valid model file path with \"model-file=<path>\"\n");

		return EXIT_FAILURE;
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge obj model loader"),
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
			(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions))
			(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive))));

	bool running =
		true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::movement_speed(
				4.0f),
			sge::camera::rotation_speed(
				200.0f),
			sys.keyboard_collector(),
			sys.mouse_collector()));

	fcppt::signal::scoped_connection const viewport_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				fcppt::ref(
					sys.renderer()),
				fcppt::ref(
					camera),
				sge::renderer::projection::fov(
					fcppt::math::deg_to_rad(
						90.f)),
				sge::renderer::projection::near(
					0.1f),
				sge::renderer::projection::far(
					1000.f))));

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::model::obj::loader_ptr const model_loader(
		sge::model::obj::create());

	sge::model::obj::instance_ptr model(
		model_loader->load(
			model_file));

	sge::renderer::texture::planar_ptr texture;
	if(!texture_file.empty())
		texture =
			sge::renderer::texture::create_planar_from_path(
				texture_file,
				sys.renderer(),
				sys.image_loader(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none);

	compiled_model compiled(
		*model,
		sys.renderer(),
		*vertex_declaration,
		texture);

	sge::line_drawer::object line_drawer(
		sys.renderer());

	if(
		sge::parse::json::find_and_convert_member<bool>(
			config,
			sge::parse::json::path(
				FCPPT_TEXT("show-normals"))))
		normals_to_line_drawer(
			compiled.vb(),
			sge::line_drawer::scoped_lock(
				line_drawer).value(),
			sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
				config,
				sge::parse::json::path(
					FCPPT_TEXT("normal-scaling"))));

	sys.renderer().light(
		sge::renderer::light::index(
			0),
		sge::renderer::light::object(
			sge::renderer::diffuse_color(
				sge::image::colors::white()),
			sge::renderer::specular_color(
				sge::image::colors::white()),
			sge::renderer::ambient_color(
				sge::image::colors::white()),
			sge::renderer::light::point(
				sge::renderer::light::position(
					sge::parse::json::find_and_convert_member<sge::renderer::light::position::value_type>(
						config,
						sge::parse::json::path(FCPPT_TEXT("light")) / FCPPT_TEXT("position"))),
				sge::renderer::light::attenuation(
					sge::renderer::light::constant_attenuation(
						sge::parse::json::find_and_convert_member<sge::renderer::light::constant_attenuation::value_type>(
							config,
							sge::parse::json::path(FCPPT_TEXT("light")) / FCPPT_TEXT("constant-attenuation"))),
					sge::renderer::light::linear_attenuation(
						sge::parse::json::find_and_convert_member<sge::renderer::light::linear_attenuation::value_type>(
							config,
							sge::parse::json::path(FCPPT_TEXT("light")) / FCPPT_TEXT("linear-attenuation"))),
					sge::renderer::light::quadratic_attenuation(
						sge::parse::json::find_and_convert_member<sge::renderer::light::quadratic_attenuation::value_type>(
							config,
							sge::parse::json::path(FCPPT_TEXT("light")) / FCPPT_TEXT("quadratic-attenuation")))))));

	sys.renderer().enable_light(
		sge::renderer::light::index(
			0),
		true);

	// We need this timer to update the camera
	sge::timer::basic<sge::timer::clocks::standard>
		frame_timer(
			sge::timer::parameters<sge::timer::clocks::standard>(
				fcppt::chrono::seconds(
					1)));

	// Set clear status
	sge::renderer::state::scoped scoped_clear_state(
		sys.renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_depth_buffer = true)
			(sge::renderer::state::float_::depth_buffer_clear_val = 1.f)
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color =
					sge::image::colors::black()));

	while(running)
	{
		sys.window().dispatch();

		// If we have no viewport (yet), don't do anything (this is just a
		// precaution, we _might_ divide by zero somewhere below, otherwise)
		if(!sge::renderer::viewport_size(sys.renderer()).content())
			continue;

		// This moves the camera around
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::duration>(
				frame_timer));

		sge::renderer::scoped_block const block_(
			sys.renderer());

		sge::renderer::scoped_transform scoped_projection(
			sys.renderer(),
			sge::renderer::matrix_mode::projection,
			camera.projection());

		sge::renderer::scoped_transform scoped_world(
			sys.renderer(),
			sge::renderer::matrix_mode::world,
			camera.world());

		line_drawer.render();

		sge::renderer::state::scoped scoped_state(
			sys.renderer(),
			sge::renderer::state::list
				(sge::renderer::state::bool_::enable_lighting =
					sge::parse::json::find_and_convert_member<bool>(
						config,
						sge::parse::json::path(FCPPT_TEXT("lighting"))))
				(
					sge::parse::json::find_and_convert_member<bool>(
						config,
						sge::parse::json::path(FCPPT_TEXT("wireframe")))
					?
						sge::renderer::state::draw_mode::line
					:
						sge::renderer::state::draw_mode::fill)
				(sge::renderer::state::depth_func::less)
				(sge::renderer::state::bool_::enable_alpha_blending = false)
				(sge::renderer::state::cull_mode::counter_clockwise));

		compiled.render();
	}
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
