//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CLEAR_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/clear/back_buffer_value_fwd.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/optional_back_buffer.hpp>
#include <sge/renderer/clear/optional_depth_buffer.hpp>
#include <sge/renderer/clear/optional_stencil_buffer.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <sge/renderer/detail/symbol.hpp>

namespace sge::renderer::clear
{

/**
\brief Clear parameters used to clear a renderer device

\ingroup sge_renderer

Clear parameters include optional clear values for
<ul>
<li>The backbuffer,</li>
<li>the depth buffer and</li>
<li>the stencil buffer</li>
</ul>
*/
class parameters
{
public:
  /**
	\brief Default constructs clear parameters

	By default nothing will be cleared.
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  parameters();

  /**
	\brief Sets the back buffer clear value
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  sge::renderer::clear::parameters &back_buffer(sge::renderer::clear::back_buffer_value const &);

  /**
	\brief Sets the depth buffer clear value
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  sge::renderer::clear::parameters &depth_buffer(sge::renderer::clear::depth_buffer_value);

  /**
	\brief Sets the stencil buffer clear value
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  sge::renderer::clear::parameters &stencil_buffer(sge::renderer::clear::stencil_buffer_value);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::clear::optional_back_buffer const &
  back_buffer() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::clear::optional_depth_buffer const &
  depth_buffer() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::clear::optional_stencil_buffer const &
  stencil_buffer() const;

private:
  sge::renderer::clear::optional_back_buffer back_buffer_;

  sge::renderer::clear::optional_depth_buffer depth_buffer_;

  sge::renderer::clear::optional_stencil_buffer stencil_buffer_;
};

}

#endif
