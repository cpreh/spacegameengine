//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/opengl/core.hpp>
#include <sge/opengl/system.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/window/system.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/system_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>

sge::opengl::core::core(fcppt::log::context_reference const _log_context)
    : sge::renderer::core(),
      log_{
          _log_context,
          sge::log::location(),
          sge::log::default_parameters(fcppt::log::name{FCPPT_TEXT("opengl")})}
{
}

sge::opengl::core::~core() = default;

sge::renderer::system_unique_ptr
sge::opengl::core::create_system(sge::window::system_ref const _system)
{
  return fcppt::unique_ptr_to_base<sge::renderer::system>(
      fcppt::make_unique_ptr<sge::opengl::system>(
          fcppt::make_ref(log_), fcppt::make_ref(_system.get().awl_system())));
}

sge::renderer::caps::system_field sge::opengl::core::caps() const
{
  return sge::renderer::caps::system_field{
      sge::renderer::caps::system::opengl, sge::renderer::caps::system::ffp};
}
