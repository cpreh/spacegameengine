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


#ifndef SGE_D3D9_STATE_CORE_SAMPLER_FILTER_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_SAMPLER_FILTER_VISITOR_HPP_INCLUDED

#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class visitor
{
public:
	typedef sge::d3d9::state::core::sampler::state_vector result_type;

	result_type const
	operator()(
		sge::renderer::state::core::sampler::filter::anisotropic::parameters const &
	) const;

	result_type const
	operator()(
		sge::renderer::state::core::sampler::filter::normal::parameters const &
	) const;
};

}
}
}
}
}
}

#endif
