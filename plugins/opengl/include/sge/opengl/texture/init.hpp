//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/extend_size.hpp>
#include <sge/opengl/texture/format_result_impl.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::texture
{

template<
	typename Types
>
std::vector<
	fcppt::unique_ptr<
		typename
		Types::buffer_types::base
	>
>
init(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	typename Types::parameters const &_parameters,
	fcppt::reference< // NOLINT(readability-avoid-const-params-in-decls)
		sge::opengl::texture::config<
			Types::buffer_types::dim_types::num_dims
		> const
	> const _config,
	sge::opengl::texture::type const _type, // NOLINT(readability-avoid-const-params-in-decls)
	sge::opengl::texture::buffer_type const _buffer_type, // NOLINT(readability-avoid-const-params-in-decls)
	sge::opengl::texture::id const _id // NOLINT(readability-avoid-const-params-in-decls)
)
{
	using
	extended_dim
	=
	sge::renderer::basic_dim<
		Types::buffer_types::dim_types::num_dims
	>;

	extended_dim const size(
		sge::opengl::texture::extend_size(
			_parameters.size()
		)
	);

	sge::opengl::texture::check_dim(
		_basic_parameters.log(),
		size,
		Types::buffer_types::dim_types::min_size(),
		Types::name()
	);

	using
	format_result_type
	=
	typename
	Types::buffer_types::format_types::format_result;

	format_result_type const format{
		Types::buffer_types::format_types::translate_format(
			_parameters.format()
		)
	};

	sge::opengl::color_order const color_order(
		Types::buffer_types::format_types::convert_order()(
			format.gl_format()
		)
	);

	sge::opengl::color_base_type const color_base_type(
		Types::buffer_types::format_types::convert_base_type()(
			format.gl_format()
		)
	);

	sge::opengl::internal_color_format const internal_color_format(
		Types::buffer_types::format_types::convert_internal_format()(
			format.gl_format()
		)
	);

	Types::buffer_types::dim_types::init_function().get()(
		_binding,
		_config.get(),
		_buffer_type,
		color_order,
		color_base_type,
		internal_color_format,
		sge::renderer::texture::mipmap::level(
			0U
		),
		size,
		nullptr
	);

	sge::opengl::texture::mipmap::create(
		_basic_parameters.log(),
		_basic_parameters.context(),
		sge::opengl::texture::mipmap::parameters<
			extended_dim::dim_wrapper::value
		>(
			fcppt::make_cref(
				_binding
			),
			_buffer_type,
			_config,
			color_order,
			color_base_type,
			internal_color_format,
			size,
			Types::buffer_types::dim_types::init_function()
		),
		_parameters.mipmap()
	);

	sge::renderer::texture::mipmap::level_count const mip_levels(
		sge::opengl::texture::mipmap::get_levels(
			_parameters.mipmap(),
			size
		)
	);

	sge::opengl::texture::is_render_target const is_target(
		_parameters.capabilities()
		&
		sge::renderer::texture::capabilities::render_target
	);

	using
	gl_buffer
	=
	typename
	Types::buffer_types::gl_buffer;

	using
	level_container
	=
	std::vector<
		fcppt::unique_ptr<
			typename
			Types::buffer_types::base
		>
	>;

	return
		fcppt::algorithm::map<
			level_container
		>(
			fcppt::make_int_range_count(
				sge::renderer::texture::mipmap::level(
					mip_levels.get()
				)
			),
			[
				&_binding,
				&_basic_parameters,
				_config,
				_type,
				_buffer_type,
				_id,
				&_parameters,
				color_order,
				color_base_type,
				format,
				internal_color_format,
				is_target
			](
				sge::renderer::texture::mipmap::level const _index
			)
			{
				return
					fcppt::unique_ptr_to_base<
						typename
						Types::buffer_types::base
					>(
						fcppt::make_unique_ptr<
							gl_buffer
						>(
							format.sge_format(),
							_config,
							sge::opengl::texture::basic_buffer_parameters(
								fcppt::make_ref(
									_basic_parameters.log()
								),
								fcppt::make_cref(
									_binding
								),
								fcppt::make_ref(
									_basic_parameters.context()
								),
								_index,
								_type,
								_buffer_type,
								_id,
								_parameters.resource_flags(),
								color_order,
								color_base_type,
								internal_color_format,
								is_target
							)
						)
					);
			}
		);
}

}

#endif
