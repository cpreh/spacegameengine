/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLE_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enable_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enable_variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


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

class enable
{
public:
	SGE_RENDERER_SYMBOL
	enable(
		sge::renderer::state::core::depth_stencil::stencil::enable_variant const &,
		sge::renderer::state::core::depth_stencil::stencil::ref,
		sge::renderer::state::core::depth_stencil::stencil::write_mask
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::enable_variant const &
	stencil::enable_variant() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::ref const
	stencil::ref() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::write_mask const
	stencil::write_mask() const;
private:
	sge::renderer::state::core::depth_stencil::stencil::enable_variant enable_variant_;

	sge::renderer::state::core::depth_stencil::stencil::ref stencil::ref_;

	sge::renderer::state::core::depth_stencil::stencil::write_mask stencil::write_mask_;
};

}
}
}
}
}
}

#endif
