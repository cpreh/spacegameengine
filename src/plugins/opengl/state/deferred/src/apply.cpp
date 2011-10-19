/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../apply.hpp"
#include "../alpha_test.hpp"
#include "../blend_func.hpp"
#include "../bundle.hpp"
#include "../color_write.hpp"
#include "../parameters_fwd.hpp"
#include "../stencil_func.hpp"
#include "../stencil_op.hpp"
#include <sge/renderer/state/list_fwd.hpp>
#include <fcppt/assert/unreachable.hpp>

void
sge::opengl::state::deferred::apply(
	deferred::parameters const &_parameters,
	deferred::bundle::type const _bundle,
	sge::renderer::state::list const &_list
)
{
	switch(
		_bundle
	)
	{
	case deferred::bundle::alpha_test:
		deferred::alpha_test(
			_parameters,
			_list
		);

		return;
	case deferred::bundle::blend_func:
		deferred::blend_func(
			_parameters,
			_list
		);

		return;
	case deferred::bundle::color_write:
		deferred::color_write(
			_parameters,
			_list
		);

		return;
	case deferred::bundle::stencil_func:
		deferred::stencil_func(
			_parameters,
			_list
		);

		return;
	case deferred::bundle::stencil_op:
		deferred::stencil_op(
			_parameters,
			_list
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
