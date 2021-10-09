//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/texture/const_base_ref.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>

sge::renderer::texture::scoped::scoped(
    sge::renderer::context::core_ref const _context,
    sge::renderer::texture::const_base_ref const _texture,
    sge::renderer::texture::stage const _stage)
    : context_(_context), stage_(_stage)
{
  context_.get().texture(sge::renderer::texture::const_optional_base_ref(_texture), stage_);
}

sge::renderer::texture::scoped::~scoped()
{
  context_.get().texture(sge::renderer::texture::const_optional_base_ref(), stage_);
}
