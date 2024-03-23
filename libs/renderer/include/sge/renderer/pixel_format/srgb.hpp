//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_PIXEL_FORMAT_SRGB_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_SRGB_HPP_INCLUDED

#include <sge/renderer/pixel_format/srgb_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::pixel_format
{

enum class srgb : std::uint8_t
{
  /**
	\brief Don't do gamma correction
	*/
  no,
  /**
	\brief Do gamma correction and fail if it is not supported
	*/
  yes,
  /**
	\brief Do gamma correction if it is supported, else do nothing
	*/
  try_
};

}

#endif
