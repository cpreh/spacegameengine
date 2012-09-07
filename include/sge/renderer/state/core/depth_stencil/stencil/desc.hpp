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


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_DESC_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_DESC_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>


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

class desc
{
public:
	SGE_RENDERER_SYMBOL
	desc(
		sge::renderer::state::core::depth_stencil::stencil::fail_op,
		sge::renderer::state::core::depth_stencil::stencil::depth_fail_op,
		sge::renderer::state::core::depth_stencil::stencil::pass_op,
		sge::renderer::state::core::depth_stencil::stencil::func::type
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::fail_op const
	fail_op() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::depth_fail_op const
	depth_fail_op() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::pass_op const
	pass_op() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::func::type
	func() const;
private:
	sge::renderer::state::core::depth_stencil::stencil::fail_op fail_op_;

	sge::renderer::state::core::depth_stencil::stencil::depth_fail_op depth_fail_op_;

	sge::renderer::state::core::depth_stencil::stencil::pass_op pass_op_;

	sge::renderer::state::core::depth_stencil::stencil::func::type func_;
};

}
}
}
}
}
}

#endif
