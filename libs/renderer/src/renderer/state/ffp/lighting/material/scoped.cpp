//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/scoped.hpp>
#include <fcppt/make_cref.hpp>


sge::renderer::state::ffp::lighting::material::scoped::scoped(
	sge::renderer::context::ffp &_context,
	sge::renderer::state::ffp::lighting::material::object const &_state
)
:
	context_(
		_context
	)
{
	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref(
			fcppt::make_cref(
				_state
			)
		)
	);
}

sge::renderer::state::ffp::lighting::material::scoped::~scoped()
{
	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref()
	);
}
