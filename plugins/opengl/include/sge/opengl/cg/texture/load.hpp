//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_TEXTURE_LOAD_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_LOAD_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge::opengl::cg::texture
{

sge::renderer::cg::loaded_texture_unique_ptr
load(
	fcppt::log::object_reference,
	sge::opengl::context::object_ref,
	sge::cg::parameter::object const &,
	sge::renderer::texture::base_ref
);

}

#endif
