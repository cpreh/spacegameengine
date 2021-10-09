//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_MANAGER_HPP_INCLUDED
#define SGE_VIEWPORT_MANAGER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/optional_resize_callback_fwd.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/viewport/detail/symbol.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>

namespace sge::viewport
{

class SGE_CORE_DETAIL_CLASS_SYMBOL manager
{
  FCPPT_NONMOVABLE(manager);

public:
  SGE_VIEWPORT_DETAIL_SYMBOL
  manager(
      sge::renderer::device::core_ref,
      sge::window::object_ref,
      sge::viewport::optional_resize_callback &&);

  SGE_VIEWPORT_DETAIL_SYMBOL
  ~manager();

  [[nodiscard]] SGE_VIEWPORT_DETAIL_SYMBOL fcppt::signal::auto_connection
  manage_callback(sge::viewport::manage_callback &&);

  SGE_VIEWPORT_DETAIL_SYMBOL
  void resize_callback(sge::viewport::optional_resize_callback &&);

  [[nodiscard]] SGE_VIEWPORT_DETAIL_SYMBOL sge::renderer::target::viewport viewport() const;

private:
  using impl_ptr = fcppt::unique_ptr<sge::viewport::detail::manager_impl>;

  impl_ptr const impl_;
};

}

#endif
