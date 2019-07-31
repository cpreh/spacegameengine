//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_CONVERT_SAMPLER_COLOR_ARG_TYPE_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_SAMPLER_COLOR_ARG_TYPE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{

template<
	typename Arg
>
struct sampler_color_arg_type;

template<>
struct sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg1
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

template<>
struct sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg2
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

template<>
struct sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg3
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

}
}
}
}

#endif
