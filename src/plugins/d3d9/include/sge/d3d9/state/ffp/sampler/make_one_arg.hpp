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


#ifndef SGE_D3D9_STATE_FFP_SAMPLER_MAKE_ONE_ARG_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_MAKE_ONE_ARG_HPP_INCLUDED

#include <sge/d3d9/state/convert/sampler_arg.hpp>
#include <sge/d3d9/state/convert/sampler_arg_type.hpp>
#include <sge/d3d9/state/ffp/sampler/state.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace sampler
{

template<
	typename OpType,
	typename Arg
>
sge::d3d9::state::ffp::sampler::state const
make_one_arg(
	Arg const _arg
)
{
	return
		sge::d3d9::state::ffp::sampler::state(
			sge::d3d9::state::convert::sampler_arg_type<
				OpType,
				Arg
			>::get(),
			sge::d3d9::state::convert::sampler_arg(
				_arg.get()
			)
		);
}

}
}
}
}
}

#endif
