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


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_COMBINED_SIMPLE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_COMBINED_SIMPLE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined_simple_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/op_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/value.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

/**
\brief A helper class to initialize a combined stencil state

This class can be used to initialize a combined stencil state by providing
default values for all options expect the function which is passed in the
constructor. The following tables lists all of the default values:

<dl>

<dt>ref</dt>
<dd>0</dd>

<dt>read_mask</dt>
<dd>~0()</dd>

<dt>write_mask</dt>
<dd>~0</dd>

<dt>fail/dept_fail/pass op</dt>
<dd>never</dd>

</dl>
*/
class combined_simple
{
	FCPPT_NONASSIGNABLE(
		combined_simple
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	combined_simple(
		sge::renderer::state::core::depth_stencil::stencil::func
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::enabled
	to_enabled() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	ref(
		sge::renderer::state::core::depth_stencil::stencil::value
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	read_mask(
		sge::renderer::state::core::depth_stencil::stencil::value
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	write_mask(
		sge::renderer::state::core::depth_stencil::stencil::value
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	fail_op(
		sge::renderer::state::core::depth_stencil::stencil::op
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	depth_fail_op(
		sge::renderer::state::core::depth_stencil::stencil::op
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::combined_simple &
	pass_op(
		sge::renderer::state::core::depth_stencil::stencil::op
	);
private:
	sge::renderer::state::core::depth_stencil::stencil::func const func_;

	sge::renderer::state::core::depth_stencil::stencil::ref ref_;

	sge::renderer::state::core::depth_stencil::stencil::read_mask read_mask_;

	sge::renderer::state::core::depth_stencil::stencil::write_mask write_mask_;

	sge::renderer::state::core::depth_stencil::stencil::fail_op fail_op_;

	sge::renderer::state::core::depth_stencil::stencil::depth_fail_op depth_fail_op_;

	sge::renderer::state::core::depth_stencil::stencil::pass_op pass_op_;
};

}
}
}
}
}
}

#endif
