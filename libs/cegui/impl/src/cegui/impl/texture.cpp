//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/to_fcppt_string.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/impl/convert_pixel_format.hpp>
#include <sge/cegui/impl/from_cegui_size.hpp>
#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/texel_scaling.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/cegui/impl/to_absolute_path.hpp>
#include <sge/cegui/impl/to_cegui_size.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/difference_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Texture.h>
#include <CEGUI/Vector.h>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::texture::texture(
	fcppt::log::object &_log,
	sge::cegui::impl::texture_parameters const &_texture_parameters,
	CEGUI::String const &_name
)
:
	texture(
		_log,
		_texture_parameters,
		_name,
		sge::cegui::impl::texture::optional_sizef(),
		sge::cegui::impl::texture::optional_texel_scaling(
			sge::cegui::impl::texture::optional_vector2f()
		),
		sge::cegui::impl::texture::optional_planar_unique_ptr()
	)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("texture(")
			<<
			this
			<<
			FCPPT_TEXT(")::texture(")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_name
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert name")
						};
				}
			)
			<<
			FCPPT_TEXT(')')
	)
}

sge::cegui::impl::texture::texture(
	fcppt::log::object &_log,
	sge::cegui::impl::texture_parameters const &_texture_parameters,
	CEGUI::String const &_name,
	CEGUI::Sizef const &_size,
	sge::renderer::texture::capabilities_field const &_caps
)
:
	texture(
		_log,
		_texture_parameters,
		_name,
		sge::cegui::impl::texture::optional_sizef{
			_size
		},
		sge::cegui::impl::texture::optional_texel_scaling(
			sge::cegui::impl::texture::optional_vector2f{
				sge::cegui::impl::texel_scaling(
					_size
				)
			}
		),
		sge::cegui::impl::texture::optional_planar_unique_ptr{
			_texture_parameters.renderer().create_planar_texture(
				sge::renderer::texture::planar_parameters(
					fcppt::math::dim::to_unsigned(
						fcppt::math::dim::structure_cast<
							fcppt::math::dim::static_<
								std::make_signed<
									sge::renderer::size_type
								>::type,
								2
							>,
							fcppt::cast::float_to_int_fun
						>(
							sge::cegui::impl::from_cegui_size(
								_size
							)
						)
					),
					sge::renderer::texture::color_format(
						sge::image::color::format::rgba8,
						_texture_parameters.emulate_srgb()
					),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					_caps
				)
			)
		}
	)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("texture(")
			<<
			this
			<<
			FCPPT_TEXT(")::texture(")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_name
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert name")
						};
				}
			)
			<<
			FCPPT_TEXT(", ")
			<<
			sge::cegui::impl::from_cegui_size(
				_size
			)
			<<
			FCPPT_TEXT(')')
	)
}

sge::cegui::impl::texture::~texture()
{
}

sge::cegui::impl::texture::optional_planar_texture_ref
sge::cegui::impl::texture::impl()
{
	return
		fcppt::optional::deref(
			texture_
		);
}

void
sge::cegui::impl::texture::create_from_view(
	sge::image2d::view::const_object const &_view
)
{
	FCPPT_ASSERT_PRE(
		!texture_.has_value()
		&&
		!size_.has_value()
		&&
		!texel_scaling_.get().has_value()
	);

	CEGUI::Sizef const new_size(
		sge::cegui::impl::to_cegui_size(
			fcppt::math::dim::structure_cast<
				fcppt::math::dim::static_<
					CEGUI::Sizef::value_type,
					2
				>,
				fcppt::cast::int_to_float_fun
			>(
				sge::image2d::view::size(
					_view
				)
			)
		)
	);

	size_ =
		sge::cegui::impl::texture::optional_sizef(
			new_size
		);

	texel_scaling_ =
		sge::cegui::impl::texture::optional_texel_scaling{
			sge::cegui::impl::texture::optional_vector2f{
				sge::cegui::impl::texel_scaling(
					new_size
				)
			}
		};

	texture_ =
		optional_planar_unique_ptr(
			sge::renderer::texture::create_planar_from_view(
				texture_parameters_.renderer(),
				_view,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				texture_parameters_.emulate_srgb()
			)
		);
}

CEGUI::String const &
sge::cegui::impl::texture::getName() const
{
	return
		name_;
}

CEGUI::Sizef const &
sge::cegui::impl::texture::getSize() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			size_
		);
}

CEGUI::Sizef const &
sge::cegui::impl::texture::getOriginalDataSize() const
{
	return
		this->getSize();
}

CEGUI::Vector2f const &
sge::cegui::impl::texture::getTexelScaling() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texel_scaling_.get()
		);
}

void
sge::cegui::impl::texture::loadFromFile(
	CEGUI::String const &_filename,
	CEGUI::String const &_resource_group
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("texture(")
			<<
			this
			<<
			FCPPT_TEXT(")::loadFromFile(")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_filename
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert filename")
						};
				}
			)
			<<
			FCPPT_TEXT(", ")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_resource_group
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert resource name")
						};
				}
			)
			<<
			FCPPT_TEXT(')')
	)

	this->create_from_view(
		sge::image2d::load_exn(
			fcppt::make_ref(
				texture_parameters_.image_system()
			),
			sge::cegui::impl::to_absolute_path(
				texture_parameters_.prefix(),
				_filename
			)
		)->view()
	);
}

void
sge::cegui::impl::texture::loadFromMemory(
	void const *const _buffer,
	CEGUI::Sizef const &_buffer_size,
	CEGUI::Texture::PixelFormat const _pixel_format
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("texture(")
			<<
			this
			<<
			FCPPT_TEXT(")::loadFromMemory(")
			<<
			sge::cegui::impl::from_cegui_size(
				_buffer_size
			)
			<<
			FCPPT_TEXT(')')
	)

	typedef
	fcppt::math::dim::static_<
		std::make_signed<
			sge::renderer::size_type
		>::type,
		2
	>
	signed_dim;

	FCPPT_ASSERT_PRE((
		fcppt::math::dim::structure_cast<
			signed_dim,
			fcppt::cast::float_to_int_fun
		>(
			sge::cegui::impl::from_cegui_size(
				this->getSize()
			)
		)
		==
		fcppt::math::dim::structure_cast<
			signed_dim,
			fcppt::cast::float_to_int_fun
		>(
			sge::cegui::impl::from_cegui_size(
				_buffer_size
			)
		)
	));

	sge::image::color::optional_format const format(
		sge::cegui::impl::convert_pixel_format(
			_pixel_format
		)
	);

	sge::renderer::texture::scoped_planar_lock const lock(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->impl()
		).get(),
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			fcppt::cast::from_void_ptr<
				sge::image::const_raw_pointer
			>(
				_buffer
			),
			fcppt::math::dim::to_unsigned(
				fcppt::math::dim::structure_cast<
					fcppt::math::dim::static_<
						sge::image::difference_type,
						2
					>,
					fcppt::cast::float_to_int_fun
				>(
					sge::cegui::impl::from_cegui_size(
						_buffer_size
					)
				)
			),
			FCPPT_ASSERT_OPTIONAL_ERROR(
				format
			),
			fcppt::math::dim::null<
				sge::image2d::pitch
			>()
		),
		lock.value(),
		sge::image::algorithm::may_overlap::no,
		sge::image::algorithm::uninitialized::yes
	);
}

void
sge::cegui::impl::texture::blitFromMemory(
	void const *,
	CEGUI::Rectf const &
)
{
	// Nothing ever calls this
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitFromMemory() is not implemented yet")
	);
}

void
sge::cegui::impl::texture::blitToMemory(
	void *
)
{
	// Nothing ever calls this
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitToMemory() is not implemented yet")
	);
}

bool
sge::cegui::impl::texture::isPixelFormatSupported(
	CEGUI::Texture::PixelFormat const _format
) const
{
	return
		sge::cegui::impl::convert_pixel_format(
			_format
		).has_value();
}

sge::cegui::impl::texture::texture(
	fcppt::log::object &_log,
	sge::cegui::impl::texture_parameters const &_texture_parameters,
	CEGUI::String const &_name,
	sge::cegui::impl::texture::optional_sizef const &_size,
	sge::cegui::impl::texture::optional_texel_scaling const _texel_scaling,
	sge::cegui::impl::texture::optional_planar_unique_ptr &&_texture
)
:
	log_{
		_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("texture")
			}
		)
	},
	texture_parameters_{
		_texture_parameters
	},
	name_{
		_name
	},
	size_{
		_size
	},
	texel_scaling_{
		_texel_scaling
	},
	texture_{
		std::move(
			_texture
		)
	}
{
}
