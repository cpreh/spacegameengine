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


#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type.hpp>


sge::renderer::state::ffp::sampler::ternary_op::ternary_op(
	sge::renderer::state::ffp::sampler::ternary_op_type const _type,
	sge::renderer::state::ffp::sampler::arg1 const _arg1,
	sge::renderer::state::ffp::sampler::arg2 const _arg2,
	sge::renderer::state::ffp::sampler::arg3 const _arg3
)
:
	type_(
		_type
	),
	arg1_(
		_arg1
	),
	arg2_(
		_arg2
	),
	arg3_(
		_arg3
	)
{
}

sge::renderer::state::ffp::sampler::ternary_op_type
sge::renderer::state::ffp::sampler::ternary_op::type() const
{
	return type_;
}

sge::renderer::state::ffp::sampler::arg1 const
sge::renderer::state::ffp::sampler::ternary_op::arg1() const
{
	return arg1_;
}

sge::renderer::state::ffp::sampler::arg2 const
sge::renderer::state::ffp::sampler::ternary_op::arg2() const
{
	return arg2_;
}

sge::renderer::state::ffp::sampler::arg3 const
sge::renderer::state::ffp::sampler::ternary_op::arg3() const
{
	return arg3_;
}
