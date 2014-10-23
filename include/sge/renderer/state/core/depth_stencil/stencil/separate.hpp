/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_SEPARATE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_SEPARATE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/back.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/front.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

class separate
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	separate(
		sge::renderer::state::core::depth_stencil::stencil::front const &,
		sge::renderer::state::core::depth_stencil::stencil::back const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::front const &
	front() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::back const &
	back() const;
private:
	sge::renderer::state::core::depth_stencil::stencil::front front_;

	sge::renderer::state::core::depth_stencil::stencil::back back_;
};

}
}
}
}
}
}

#endif
