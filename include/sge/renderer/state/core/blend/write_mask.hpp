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


#ifndef SGE_RENDERER_STATE_CORE_BLEND_WRITE_MASK_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_WRITE_MASK_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/write_alpha.hpp>
#include <sge/renderer/state/core/blend/write_blue.hpp>
#include <sge/renderer/state/core/blend/write_green.hpp>
#include <sge/renderer/state/core/blend/write_mask_fwd.hpp>
#include <sge/renderer/state/core/blend/write_red.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace blend
{

class write_mask
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	write_mask(
		sge::renderer::state::core::blend::write_red,
		sge::renderer::state::core::blend::write_blue,
		sge::renderer::state::core::blend::write_green,
		sge::renderer::state::core::blend::write_alpha
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_red const
	write_red() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_blue const
	write_blue() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_green const
	write_green() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_alpha const
	write_alpha() const;
private:
	sge::renderer::state::core::blend::write_red write_red_;

	sge::renderer::state::core::blend::write_blue write_blue_;

	sge::renderer::state::core::blend::write_green write_green_;

	sge::renderer::state::core::blend::write_alpha write_alpha_;
};

}
}
}
}
}

#endif
