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


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
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
	SGE_RENDERER_SYMBOL
	parameters(
		sge::renderer::state::core::sampler::filter::normal::mag::type,
		sge::renderer::state::core::sampler::filter::normal::min::type,
		sge::renderer::state::core::sampler::filter::normal::mip::type
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mag::type
	mag() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::min::type
	min() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mip::type
	mip() const;
private:
	sge::renderer::state::core::sampler::filter::normal::mag::type mag_;

	sge::renderer::state::core::sampler::filter::normal::min::type min_;

	sge::renderer::state::core::sampler::filter::normal::mip::type mip_;
};

SGE_RENDERER_SYMBOL
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
