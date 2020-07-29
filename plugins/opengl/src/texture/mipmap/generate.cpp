//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/context.hpp>
#include <sge/opengl/texture/mipmap/generate.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


void
sge::opengl::texture::mipmap::generate(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type
)
{
	fcppt::optional::to_exception(
		sge::opengl::context::use<
			sge::opengl::texture::mipmap::context
		>(
			fcppt::make_ref(
				_context
			),
			_context.info()
		).generate_mipmap(),
		[]{
			return
				sge::renderer::unsupported(
					FCPPT_TEXT("GenerateMipmaps"),
					FCPPT_TEXT("GL_VERSION_3_0"),
					FCPPT_TEXT("glGenerateMipmapsEXT")
				);
		}
	).get()(
		_type.get()
	);
}
