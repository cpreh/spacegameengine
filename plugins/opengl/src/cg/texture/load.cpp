//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/cg/texture/load.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>


sge::renderer::cg::loaded_texture_unique_ptr
sge::opengl::cg::texture::load(
	fcppt::log::object_reference const _log,
	sge::opengl::context::object_ref const _context,
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base_ref const _texture
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::cg::loaded_texture
		>(
			fcppt::make_unique_ptr<
				sge::opengl::cg::texture::loaded_object
			>(
				_log,
				_context,
				_parameter,
				_texture
			)
		);
}
