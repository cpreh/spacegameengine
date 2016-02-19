/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


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
namespace normal
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::sampler::filter::normal::mag,
		sge::renderer::state::core::sampler::filter::normal::min,
		sge::renderer::state::core::sampler::filter::normal::mip
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mag
	mag() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::min
	min() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mip
	mip() const;
private:
	sge::renderer::state::core::sampler::filter::normal::mag mag_;

	sge::renderer::state::core::sampler::filter::normal::min min_;

	sge::renderer::state::core::sampler::filter::normal::mip mip_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::filter::normal::parameters const &,
	sge::renderer::state::core::sampler::filter::normal::parameters const &
);

}
}
}
}
}
}
}

#endif
