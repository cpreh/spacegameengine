//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_BLEND_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_BLEND_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/state/core/blend/config_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace blend
{

class config
{
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLBLENDFUNCSEPARATEPROC
	>
	gl_blend_func_separate;

	explicit
	config(
		gl_blend_func_separate
	);

	gl_blend_func_separate
	blend_func_separate() const;
private:
	gl_blend_func_separate blend_func_separate_;
};

}
}
}
}
}

#endif
