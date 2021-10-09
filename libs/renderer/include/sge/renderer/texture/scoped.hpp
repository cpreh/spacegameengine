//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/const_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::texture
{

class scoped
{
  FCPPT_NONMOVABLE(scoped);

public:
  SGE_RENDERER_DETAIL_SYMBOL
  scoped(
      sge::renderer::context::core_ref,
      sge::renderer::texture::const_base_ref,
      sge::renderer::texture::stage);

  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped();

private:
  sge::renderer::context::core_ref const context_;

  sge::renderer::texture::stage const stage_;
};

}

#endif
