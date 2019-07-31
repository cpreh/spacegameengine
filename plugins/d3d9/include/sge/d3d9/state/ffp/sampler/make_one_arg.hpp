//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
