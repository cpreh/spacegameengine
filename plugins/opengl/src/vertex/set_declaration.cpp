//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vertex/set_declaration.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/map.hpp>


void
sge::opengl::vertex::set_declaration(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::const_optional_declaration_ref const &_opt_declaration
)
{
	sge::opengl::context::use<
		sge::opengl::vertex::context
	>(
		_context
	).vertex_declaration(
		fcppt::optional::map(
			_opt_declaration,
			[](
				fcppt::reference<
					sge::renderer::vertex::declaration const
				> const _declaration
			)
			{
				return
					fcppt::make_cref(
						fcppt::cast::static_downcast<
							sge::opengl::vertex::declaration const &
						>(
							_declaration.get()
						)
					);
			}
		)
	);
}
