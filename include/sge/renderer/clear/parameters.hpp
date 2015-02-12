/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_CLEAR_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/clear/back_buffer_value_fwd.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/optional_back_buffer.hpp>
#include <sge/renderer/clear/optional_depth_buffer.hpp>
#include <sge/renderer/clear/optional_stencil_buffer.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <sge/renderer/detail/symbol.hpp>


namespace sge
{
namespace renderer
{
namespace clear
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
	sge::renderer::clear::parameters &
	back_buffer(
		sge::renderer::clear::back_buffer_value const &
	);

	/**
	\brief Sets the depth buffer clear value
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::clear::parameters &
	depth_buffer(
		sge::renderer::clear::depth_buffer_value
	);

	/**
	\brief Sets the stencil buffer clear value
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::clear::parameters &
	stencil_buffer(
		sge::renderer::clear::stencil_buffer_value
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::clear::optional_back_buffer const &
	back_buffer() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::clear::optional_depth_buffer const &
	depth_buffer() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::clear::optional_stencil_buffer const &
	stencil_buffer() const;
private:
	sge::renderer::clear::optional_back_buffer back_buffer_;

	sge::renderer::clear::optional_depth_buffer depth_buffer_;

	sge::renderer::clear::optional_stencil_buffer stencil_buffer_;
};

}
}
}

#endif
