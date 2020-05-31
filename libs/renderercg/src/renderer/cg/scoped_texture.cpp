//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/cg/const_loaded_texture_ref.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::renderer::cg::scoped_texture::scoped_texture(
	sge::renderer::context::core_ref const _context,
	sge::renderer::cg::const_loaded_texture_ref const _texture
)
:
	context_(
		_context
	),
	texture_(
		_texture
	),
	stage_(
		context_.get().set_cg_texture(
			texture_
		)
	)
{
}

sge::renderer::cg::scoped_texture::~scoped_texture()
{
	context_.get().unset_cg_texture(
		texture_.get()
	);
}

sge::renderer::texture::stage
sge::renderer::cg::scoped_texture::stage() const
{
	return
		stage_;
}
