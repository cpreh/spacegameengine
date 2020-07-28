//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_SET_ARRAY_HPP_INCLUDED
#define SGE_OPENGL_STATE_SET_ARRAY_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/renderer/state/index_count.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename GLState,
	typename Context,
	typename States,
	typename ConvertFunction
>
void
set_array(
	Context &_context, // NOLINT(google-runtime-references)
	States const &_states,
	ConvertFunction const &_convert_function
)
{
	auto const count(
		static_cast<
			sge::renderer::state::index_count
		>(
			_states.size()
		)
	);

	for(
		sge::renderer::state::index_count index(
			0U
		);
		index < count;
		++index
	)
	{
		GLenum const gl_index(
			_convert_function(
				index
			)
		);

		sge::opengl::enable(
			gl_index
		);

		static_cast<
			GLState const &
		>(
			_states[
				index
			].get()
		).set(
			gl_index
		);
	}

	for(
		sge::renderer::state::index_count index(
			count
		);
		index < _context.indices();
		++index
	)
	{
		sge::opengl::disable(
			_convert_function(
				index
			)
		);
	}

	_context.indices(
		count
	);
}

}
}
}

#endif
