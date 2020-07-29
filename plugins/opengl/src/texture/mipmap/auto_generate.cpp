//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/opengl/texture/mipmap/auto_generate.hpp>
#include <sge/opengl/texture/mipmap/context.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::texture::mipmap::auto_generate(
	fcppt::log::object &_log,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::object &_context
)
{
	fcppt::optional::maybe(
		sge::opengl::context::use<
			sge::opengl::texture::mipmap::context
		>(
			fcppt::make_ref(
				_context
			),
			_context.info()
		).generate_mipmap_flag(),
		[
			&_log
		]{
			FCPPT_LOG_ERROR(
				_log,
				fcppt::log::out
					<< FCPPT_TEXT("Building mipmaps is not supported.")
					<< FCPPT_TEXT(" The mip_filter will not work correctly.")
			)
		},
		[
			&_binding
		](
			GLenum const _generate_mipmap_flag
		)
		{
			sge::opengl::texture::funcs::parameter_int(
				_binding,
				_generate_mipmap_flag,
				GL_TRUE
			);
		}
	);
}
