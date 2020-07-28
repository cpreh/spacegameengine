//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_SET_DEFAULTS_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SET_DEFAULTS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{

void
set_defaults(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::opengl::context::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}
}
}

#endif
