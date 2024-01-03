//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DISPLAY_MODE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/display_mode/parameters_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/display_mode/vsync.hpp>

namespace sge::renderer::display_mode
{

/**
\brief Parameters used to set a display mode.

\see sge::renderer::system::create_device
*/
class parameters
{
public:
  // TODO(philipp): Remove this
  SGE_RENDERER_DETAIL_SYMBOL
  parameters(
      sge::renderer::display_mode::vsync, sge::renderer::display_mode::optional_object const &);

  SGE_RENDERER_DETAIL_SYMBOL
  parameters(sge::renderer::display_mode::vsync, sge::renderer::display_mode::optional_fullscreen);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::display_mode::vsync vsync() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::display_mode::optional_fullscreen const &
  fullscreen() const;

private:
  sge::renderer::display_mode::vsync vsync_;

  sge::renderer::display_mode::optional_fullscreen fullscreen_;
};

}

#endif
