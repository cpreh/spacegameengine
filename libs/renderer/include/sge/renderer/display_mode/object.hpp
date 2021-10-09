//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DISPLAY_MODE_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_OBJECT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>

namespace sge::renderer::display_mode
{

/**
\brief Describes a display mode's pixel count, dimensions and refresh rate

This class is used to change the display mode of a monitor. Note, that the bit
depth of the display mode is not part of this structure because it is chosen by
the pixel format.
*/
class object
{
public:
  /**
	\brief Constructs a display mode

	\param pixel_size The size of the display mode in pixels

	\param dimensions The dimensions of the occupied space in millimeters

	\param refresh_rate The optional refresh rate in Hz. If this is empty,
	it means the default refresh rate.
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  object(
      sge::renderer::display_mode::pixel_size pixel_size,
      sge::renderer::display_mode::optional_dimensions dimensions,
      sge::renderer::display_mode::optional_refresh_rate refresh_rate);

  /**
	\brief Returns the pixel size
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::display_mode::pixel_size const &
  pixel_size() const;

  /**
	\brief Returns the dimensions
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::display_mode::optional_dimensions const &
  dimensions() const;

  /**
	\brief Returns the refresh rate
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::display_mode::optional_refresh_rate
  refresh_rate() const;

private:
  sge::renderer::display_mode::pixel_size pixel_size_;

  sge::renderer::display_mode::optional_dimensions dimensions_;

  sge::renderer::display_mode::optional_refresh_rate refresh_rate_;
};

}

#endif
