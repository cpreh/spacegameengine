//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/render_context/create.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>


sge::renderer::context::ffp_unique_ptr
sge::opengl::render_context::create(
	fcppt::log::object_reference const _log,
	sge::opengl::context::object_ref const _context,
	sge::renderer::target::base_ref const _target
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::context::ffp
		>(
			fcppt::make_unique_ptr<
				sge::opengl::render_context::object
			>(
				_log,
				_context,
				_target
			)
		);
}
