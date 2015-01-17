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


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_ANISOTROPIC_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_ANISOTROPIC_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/level.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{
namespace anisotropic
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::sampler::filter::anisotropic::mip,
		sge::renderer::state::core::sampler::filter::anisotropic::level
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::anisotropic::mip
	mip() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::anisotropic::level const
	level() const;
private:
	sge::renderer::state::core::sampler::filter::anisotropic::mip mip_;

	sge::renderer::state::core::sampler::filter::anisotropic::level level_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &,
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &
);

}
}
}
}
}
}
}

#endif
