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


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_UNARY_OP_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_UNARY_OP_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace sampler
{

class unary_op
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	unary_op(
		sge::renderer::state::ffp::sampler::unary_op_type,
		sge::renderer::state::ffp::sampler::arg1
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::unary_op_type
	type() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::arg1 const
	arg1() const;
private:
	sge::renderer::state::ffp::sampler::unary_op_type type_;

	sge::renderer::state::ffp::sampler::arg1 arg1_;
};

}
}
}
}
}

#endif
