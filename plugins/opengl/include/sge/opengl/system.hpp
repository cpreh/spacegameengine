//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/system_fwd.hpp>
#include <sge/opengl/platform/system_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sge::opengl
{

class system : public sge::renderer::system
{
  FCPPT_NONMOVABLE(system);

public:
  system(fcppt::log::object_reference, awl::system::object_ref);

  ~system() override;

private:
  [[nodiscard]] sge::renderer::device::core_unique_ptr
  create_core_renderer(sge::renderer::device::parameters const &) override;

  [[nodiscard]] sge::renderer::device::ffp_unique_ptr
  create_ffp_renderer(sge::renderer::device::parameters const &) override;

  [[nodiscard]] awl::visual::object_unique_ptr
  create_visual(sge::renderer::pixel_format::object const &) override;

  using platform_system_unique_ptr = fcppt::unique_ptr<sge::opengl::platform::system>;

  fcppt::log::object_reference const log_;

  platform_system_unique_ptr const platform_system_;

  using backend_system_unique_ptr = fcppt::unique_ptr<sge::opengl::backend::system>;

  backend_system_unique_ptr const backend_system_;
};

}

#endif
