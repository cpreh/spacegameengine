//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/scoped_scissor_area.hpp>


sge::renderer::target::scoped_scissor_area::scoped_scissor_area(
	sge::renderer::target::base_ref const _target,
	sge::renderer::target::scissor_area const &_new_scissor_area
)
:
	target_(
		_target
	),
	old_area_(
		target_.get().scissor_area()
	)
{
	target_.get().scissor_area(
		_new_scissor_area
	);
}

sge::renderer::target::scoped_scissor_area::~scoped_scissor_area()
{
	target_.get().scissor_area(
		old_area_
	);
}
