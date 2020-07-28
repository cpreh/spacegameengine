//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/set_or_default_single.hpp>
#include <sge/opengl/state/ffp/fog/default_context.hpp>
#include <sge/opengl/state/ffp/fog/object.hpp>
#include <sge/opengl/state/ffp/fog/set.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref.hpp>
#include <fcppt/make_ref.hpp>


void
sge::opengl::state::ffp::fog::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::fog::const_optional_object_ref const &_state
)
{
	sge::opengl::state::set_or_default_single<
		sge::opengl::state::ffp::fog::object
	>(
		sge::opengl::context::use<
			sge::opengl::state::ffp::fog::default_context
		>(
			fcppt::make_ref(
				_context
			)
		),
		_state
	);
}
