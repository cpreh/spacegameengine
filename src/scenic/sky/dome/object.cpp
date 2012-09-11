#include <sge/camera/base.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/set_address_mode2.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/scenic/sky/dome/index_format.hpp>
#include <sge/scenic/sky/dome/object.hpp>
#include <sge/scenic/sky/dome/vf/format.hpp>
#include <sge/scenic/sky/dome/vf/format_part.hpp>
#include <sge/scenic/sky/dome/vf/position.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::renderer::vector3 const
sphere_point(
	sge::renderer::scalar const radius,
	sge::renderer::scalar const lat,
	sge::renderer::scalar const lon)
{
	return
		radius *
		sge::renderer::vector3(
			std::cos(lon) * std::sin(lat),
			std::cos(lat),
			std::sin(lon) * std::sin(lat));
}
}

sge::scenic::sky::dome::object::object(
	sge::renderer::device &_renderer,
	sge::shader::context &_shader_context,
	sge::scenic::texture_manager &_texture_manager,
	sge::scenic::sky::dome::texture_path const &_texture_path,
	sge::camera::base &_camera,
	sge::scenic::sky::dome::longitude const &_longitude,
	sge::scenic::sky::dome::latitude const &_latitude,
	sge::scenic::sky::dome::y_translation const &_y_translation)
:
	y_translation_(
		_y_translation),
	texture_manager_(
		_texture_manager),
	texture_path_(
		_texture_path),
	renderer_(
		_renderer),
	camera_(
		_camera),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<sge::scenic::sky::dome::vf::format>())),
	vertex_buffer_(
		renderer_.create_vertex_buffer(
			*vertex_declaration_,
			sge::renderer::vf::dynamic::make_part_index
			<
				sge::scenic::sky::dome::vf::format,
				sge::scenic::sky::dome::vf::format_part
			>(),
			sge::renderer::vertex_count(
				1u + _latitude.get() * _longitude.get()),
			sge::renderer::resource_flags_field::null())),
	index_buffer_(
		renderer_.create_index_buffer(
			sge::renderer::index::dynamic::make_format<sge::scenic::sky::dome::index_format>(),
			sge::renderer::index_count(
				// For each pair of rings we have "it_lon" quads. We have
				// "it_lat-1" rings and "it_lat-2" pairs of rings.  This makes for
				// "it_lat-2" quads, each having 2 triangles and each triangle has
				// 3 indices.
				// the quads
				(_latitude.get()-1) * _longitude.get() * 2u * 3u +
				// the triangles
				_longitude.get() * 3u),
			sge::renderer::resource_flags_field::null())),
	shader_(
		_shader_context,
		*vertex_declaration_,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("skydome.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("skydome.cg")),
		sge::shader::optional_cflags()),
	mvp_parameter_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			sge::cg::string(
				"mvp")),
		_renderer,
		sge::shader::parameter::is_projection_matrix(
			true),
		sge::renderer::matrix4()),
	texture_parameter_(
		shader_,
		renderer_,
		shader_.pixel_program(),
		sge::shader::parameter::name(
			sge::cg::string(
				"sky_texture")),
		sge::shader::parameter::planar_texture::optional_value())
{
	sge::renderer::scoped_vertex_lock vblock(
		*vertex_buffer_,
		sge::renderer::lock_mode::writeonly);

	sge::renderer::vf::view<sge::scenic::sky::dome::vf::format_part> vertices(
		vblock.value());

	sge::renderer::vf::view<sge::scenic::sky::dome::vf::format_part>::iterator vb_it(
		vertices.begin());

	sge::renderer::scalar const halfpi =
		fcppt::math::pi<sge::renderer::scalar>() /
		static_cast<sge::renderer::scalar>(
			2);

	sge::renderer::scalar const radius =
		1.0f;

	// The top
	vb_it->set<sge::scenic::sky::dome::vf::position>(
		sphere_point(
			radius,
			static_cast<sge::renderer::scalar>(0),
			static_cast<sge::renderer::scalar>(0)));

	vb_it->set<sge::scenic::sky::dome::vf::texcoord>(
		sge::renderer::vector2::null());

	vb_it++;

	sge::renderer::scalar const
		increment_lat =
			halfpi /
			static_cast<sge::renderer::scalar>(
				_latitude.get()),
		increment_lon =
			fcppt::math::twopi<sge::renderer::scalar>()/
			static_cast<sge::renderer::scalar>(
				_longitude.get());

	sge::renderer::scalar lat =
		increment_lat;

	// We make one less iteration because we don't want the top
	// NOTE: We use size_type here FOR A REASON! floating point loops are inaccurate
	for (
		sge::scenic::sky::dome::size_type i =
			0u;
		i < _latitude.get();
		++i)
	{
		sge::renderer::scalar lon =
			static_cast<sge::renderer::scalar>(
				0);

		for(
			sge::scenic::sky::dome::size_type j = 0u;
			j < _longitude.get();
			++j)
		{
			sge::renderer::vector3 const
				position(
					sphere_point(
						radius,
						lat,
						lon));

			vb_it->set<sge::scenic::sky::dome::vf::position>(
				position);

			(vb_it++)->set<sge::scenic::sky::dome::vf::texcoord>(
				sge::renderer::vector2(
					0.5f -
					std::atan2(
						position.z(),
						position.x()) /
					fcppt::math::twopi<sge::renderer::scalar>(),
					0.5f -
					2.0f *
					std::asin(
						position.y()) /
					fcppt::math::twopi<sge::renderer::scalar>()));

			lon += increment_lon;
		}
		lat += increment_lat;
	}

	sge::renderer::scoped_index_lock const iblock(
		*index_buffer_,
		sge::renderer::lock_mode::writeonly);

	typedef
	sge::renderer::index::view<sge::scenic::sky::dome::index_format>
	index_view;

	index_view const view(
		iblock.value());

	index_view::iterator it(
		view.begin());

	// First, the triangles at the top
	for(
		sge::scenic::sky::dome::size_type lons =
			1u;
		lons <= _longitude.get();
		++lons)
	{
		(*it++).set(
			static_cast<index_view::value_type>(
				0u));
		(*it++).set(
			static_cast<index_view::value_type>(
				lons == _longitude.get() ? 1u : (lons+1u)));
		(*it++).set(
			static_cast<index_view::value_type>(
				lons));
	}

	// Start at the first vertex after the top
	index_view::value_type current =
		1u;

	// Again, we have it_lat-1 ring pairs (see below)
	for(
		sge::scenic::sky::dome::size_type lats =
			0u;
		lats < static_cast<sge::scenic::sky::dome::size_type>(_latitude.get()-1u);
		++lats)
	{
		// Remember the beginning index of the current circle so we can wrap around later in the inner loop
		index_view::value_type const beginning =
			current;

		// The last index would wrap around the first one, so it_lon-1
		for(
			sge::scenic::sky::dome::size_type lon =
				0u;
			lon < static_cast<sge::scenic::sky::dome::size_type>(_longitude.get());
			++lon)
		{
			index_view::value_type const
				next =
					lon == static_cast<size_type>(_longitude.get()-1u)
					?
						static_cast<index_view::value_type>(
							beginning)
					:
						static_cast<index_view::value_type>(
							current+1u),
				below =
					static_cast<index_view::value_type>(
						current + _longitude.get()),
				next_below =
					lon == static_cast<size_type>(_longitude.get()-1)
					?
						static_cast<index_view::value_type>(
							beginning + _longitude.get())
					:
						static_cast<index_view::value_type>(
							below+1);

			(*it++).set(
				current);

			(*it++).set(
				next_below);

			(*it++).set(
				below);

			(*it++).set(
				current);

			(*it++).set(
				next_below);

			(*it++).set(
				next);

			++current;
		}
	}
}

void
sge::scenic::sky::dome::object::render(
	sge::renderer::context::object &_context)
{
	texture_parameter_.set(
		sge::shader::parameter::planar_texture::optional_value(
			texture_manager_.texture_for_path(
				texture_path_.get())));

	sge::renderer::state::scoped scoped_state(
		_context,
		sge::renderer::state::list
			(sge::renderer::state::depth_func::off));

	sge::renderer::scoped_vertex_declaration scoped_vd(
		_context,
		*vertex_declaration_);

	sge::shader::scoped_pair scoped_shader(
		_context,
		shader_);

	sge::renderer::scoped_vertex_buffer scoped_vb(
		_context,
		*vertex_buffer_);

	mvp_parameter_.set(
		camera_.projection_matrix().get() *
		sge::camera::matrix_conversion::world(
			sge::camera::coordinate_system::object(
				camera_.coordinate_system().right(),
				camera_.coordinate_system().up(),
				camera_.coordinate_system().forward(),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3(
						0.0f,
						y_translation_.get(),
						0.0f)))));

	sge::renderer::texture::set_address_mode2(
		_context,
		texture_parameter_.stage(),
		sge::renderer::texture::address_mode2(
			sge::renderer::texture::address_mode::repeat));

	_context.render_indexed(
		*index_buffer_,
		sge::renderer::first_vertex(
			0u),
		sge::renderer::vertex_count(
			vertex_buffer_->size()),
		sge::renderer::primitive_type::triangle_list,
		sge::renderer::first_index(
			0u),
		sge::renderer::index_count(
			index_buffer_->size()));
}

sge::scenic::sky::dome::object::~object()
{
}
