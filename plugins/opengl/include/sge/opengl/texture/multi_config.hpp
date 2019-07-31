//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/texture/multi_config_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class multi_config
{
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLACTIVETEXTUREPROC
	>
	gl_active_texture;

	// TODO: mesa headers are broken
	//PFNGLCLIENTACTIVETEXTUREPROC
	typedef
	PFNGLACTIVETEXTUREPROC
	gl_client_active_texture_proc;

	typedef
	sge::opengl::fun_ref<
		gl_client_active_texture_proc
	>
	gl_client_active_texture;

	multi_config(
		gl_active_texture,
		gl_client_active_texture,
		sge::renderer::caps::texture_stages
	);

	gl_active_texture
	active_texture() const;

	gl_client_active_texture
	client_active_texture() const;

	sge::renderer::caps::texture_stages
	max_level() const;
private:
	gl_active_texture active_texture_;

	gl_client_active_texture client_active_texture_;

	sge::renderer::caps::texture_stages max_level_;
};

}
}
}

#endif
