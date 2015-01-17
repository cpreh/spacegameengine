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


#ifndef SGE_RENDERER_STATE_CORE_RASTERIZER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_RASTERIZER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace rasterizer
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::rasterizer::cull_mode,
		sge::renderer::state::core::rasterizer::fill_mode,
		sge::renderer::state::core::rasterizer::enable_scissor_test
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::cull_mode
	cull_mode() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::fill_mode
	fill_mode() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::enable_scissor_test const
	enable_scissor_test() const;
private:
	sge::renderer::state::core::rasterizer::cull_mode cull_mode_;

	sge::renderer::state::core::rasterizer::fill_mode fill_mode_;

	sge::renderer::state::core::rasterizer::enable_scissor_test enable_scissor_test_;
};

}
}
}
}
}

#endif
