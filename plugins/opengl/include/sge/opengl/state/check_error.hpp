//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CHECK_ERROR_HPP_INCLUDED
#define SGE_OPENGL_STATE_CHECK_ERROR_HPP_INCLUDED

#include <sge/opengl/check_state_always.hpp>
#include <fcppt/string.hpp>
#if defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
#include <sge/opengl/check_state.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#endif


namespace sge
{
namespace opengl
{
namespace state
{

inline
void
check_error(
#if defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
	fcppt::string const &_what
#else
	fcppt::string const &
#endif
)
{
#if defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
	SGE_OPENGL_CHECK_STATE(
		_what
		+
		FCPPT_TEXT(" failed!"),
		sge::renderer::exception
	)
#endif
}

}
}
}

#endif
