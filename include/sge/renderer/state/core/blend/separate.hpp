/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_STATE_CORE_BLEND_SEPARATE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_SEPARATE_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/separate_fwd.hpp>


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

class separate
{
public:
	SGE_RENDERER_SYMBOL
	separate(
		sge::renderer::state::core::blend::color_source,
		sge::renderer::state::core::blend::color_dest,
		sge::renderer::state::core::blend::alpha_source,
		sge::renderer::state::core::blend::alpha_dest
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::blend::color_source const
	color_source() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::blend::color_dest const
	color_dest() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::blend::alpha_source const
	alpha_source() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::blend::alpha_dest const
	alpha_dest() const;
private:
	sge::renderer::state::core::blend::color_source color_source_;

	sge::renderer::state::core::blend::color_dest color_dest_;

	sge::renderer::state::core::blend::alpha_source alpha_source_;

	sge::renderer::state::core::blend::alpha_dest alpha_dest_;
};

}
}
}
}
}

#endif
