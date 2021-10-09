//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_EVENT_BASE_HPP_INCLUDED
#define SGE_RENDERER_EVENT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/event/base_fwd.hpp>
#include <awl/window/reference.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base : public awl::window::event::base
{
  FCPPT_NONMOVABLE(base);

public:
  SGE_RENDERER_DETAIL_SYMBOL
  explicit base(awl::window::reference);

  SGE_RENDERER_DETAIL_SYMBOL
  ~base() override;
};

}

#endif
