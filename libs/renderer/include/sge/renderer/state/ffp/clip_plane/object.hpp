//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_CLIP_PLANE_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_CLIP_PLANE_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::state::ffp::clip_plane
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
  FCPPT_NONMOVABLE(object);

protected:
  SGE_RENDERER_DETAIL_SYMBOL
  object();

public:
  SGE_RENDERER_DETAIL_SYMBOL
  virtual ~object();
};

}

#endif
