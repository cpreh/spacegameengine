//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_CLIENT_STATE_COMBINER_REF_HPP_INCLUDED
#define SGE_OPENGL_VF_CLIENT_STATE_COMBINER_REF_HPP_INCLUDED

#include <sge/opengl/vf/client_state_combiner_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::opengl::vf
{

using
client_state_combiner_ref
=
fcppt::reference<
	sge::opengl::vf::client_state_combiner
>;

}

#endif
