//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CORE_HPP_INCLUDED
#define SGE_OPENGL_CORE_HPP_INCLUDED

#include <sge/renderer/core.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/window/system_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>

namespace sge::opengl
{

class core : public sge::renderer::core
{
  FCPPT_NONMOVABLE(core);

public:
  explicit core(fcppt::log::context_reference);

  ~core() override;

private:
  [[nodiscard]] sge::renderer::system_unique_ptr create_system(sge::window::system_ref) override;

  [[nodiscard]] sge::renderer::caps::system_field caps() const override;

  fcppt::log::object log_;
};

}

#endif
