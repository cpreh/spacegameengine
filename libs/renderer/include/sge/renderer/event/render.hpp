//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_EVENT_RENDER_HPP_INCLUDED
#define SGE_RENDERER_EVENT_RENDER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/event/base.hpp>
#include <sge/renderer/event/render_fwd.hpp>
#include <awl/window/reference.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL render : public sge::renderer::event::base
{
  FCPPT_NONMOVABLE(render);

public:
  // TODO(philipp): Which parameters do we want?
  SGE_RENDERER_DETAIL_SYMBOL
  explicit render(awl::window::reference);

  SGE_RENDERER_DETAIL_SYMBOL
  ~render() override;
};

}

#endif
