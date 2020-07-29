//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/log/object_reference.hpp>


sge::opengl::vertex::declaration::declaration(
	fcppt::log::object_reference const _log,
	sge::opengl::context::object_ref const _context,
	sge::renderer::vertex::declaration_parameters const &_parameters
)
:
	sge::renderer::vertex::declaration(),
	format_(
		_parameters.format()
	),
	parts_(
		fcppt::algorithm::map<
			part_container
		>(
			format_.parts(),
			[
				_log,
				_context
			](
				sge::renderer::vf::dynamic::part const &_part
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::opengl::vf::part
					>(
						_log,
						_context,
						sge::renderer::vf::dynamic::part{
							_part
						}
					);

			}
		)
	)
{
}

sge::opengl::vertex::declaration::~declaration()
= default;

sge::renderer::vf::dynamic::part const &
sge::opengl::vertex::declaration::format_part(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		format_.parts().at(
			_part.get()
		);
}

sge::opengl::vf::part const &
sge::opengl::vertex::declaration::gl_format_part(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		*parts_.at(
			_part.get()
		);
}
