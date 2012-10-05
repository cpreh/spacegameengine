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


#ifndef SGE_D3D9_STATE_CONVERT_SAMPLER_ALPHA_ARG_TYPE_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_SAMPLER_ALPHA_ARG_TYPE_HPP_INCLUDED

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
struct sampler_alpha_arg_type;

template<>
struct sampler_alpha_arg_type<
	sge::renderer::state::ffp::sampler::arg1
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

template<>
struct sampler_alpha_arg_type<
	sge::renderer::state::ffp::sampler::arg2
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

template<>
struct sampler_alpha_arg_type<
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
