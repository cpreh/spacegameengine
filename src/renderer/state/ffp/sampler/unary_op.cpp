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


#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>


sge::renderer::state::ffp::sampler::unary_op::unary_op(
	sge::renderer::state::ffp::sampler::unary_op_type::type const _type,
	sge::renderer::state::ffp::sampler::arg1 const _arg1
)
:
	type_(
		_type
	),
	arg1_(
		_arg1
	)
{
}

sge::renderer::state::ffp::sampler::unary_op_type::type
sge::renderer::state::ffp::sampler::unary_op::type() const
{
	return type_;
}

sge::renderer::state::ffp::sampler::arg1 const
sge::renderer::state::ffp::sampler::unary_op::arg1() const
{
	return arg1_;
}
