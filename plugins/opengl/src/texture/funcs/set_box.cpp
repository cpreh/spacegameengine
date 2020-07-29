//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/funcs/set_box.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_box.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>


void
sge::opengl::texture::funcs::set_box(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &_context,
	sge::opengl::texture::volume_config const &_config,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::color_order const _format,
	sge::opengl::color_base_type const _format_type,
	sge::renderer::texture::mipmap::level const _level,
	sge::renderer::dim3 const &_dim,
	sge::renderer::lock_box const &_lock_box,
	sge::renderer::const_raw_pointer const _src
)
{
	if(
		_src
		==
		nullptr
		&&
		!sge::opengl::context::use<
			sge::opengl::buffer::pbo_context
		>(
			fcppt::make_ref(
				_context
			),
			fcppt::make_ref(
				_context
			)
		)
		.unpack_buffer()
		.native()
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("OpenGL: Texture source is 0 although no PBO is bound!")
			};
	}

	if(
		!sge::opengl::range_check(
			_dim,
			_lock_box
		)
	)
	{
		throw
			sge::renderer::exception{
				(
					fcppt::format(
						FCPPT_TEXT("box for setting a texture is out of range (box=%1%, dim=%2%)!")
					)
					% _lock_box
					% _dim
				)
				.str()
			};
	}

	sge::renderer::lock_box::dim const lock_size(
		_lock_box.size()
	);

	sge::opengl::call_fun_ref(
		_config.tex_sub_image_3d(),
		_buffer_type.get(),
		fcppt::cast::to_signed(
			_level.get()
		),
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_lock_box.left()
			)
		),
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_lock_box.top()
			)
		),
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_lock_box.front()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				lock_size.w()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				lock_size.h()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				lock_size.d()
			)
		),
		_format.get(),
		_format_type.get(),
		fcppt::cast::to_void_ptr(
			_src
		)
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glTexSubImage3D with (box=%1%, dim=%2%) failed")
			)
			% _lock_box
			% _dim
		).str(),
		sge::renderer::exception
	)
}
