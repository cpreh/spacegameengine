//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_CONTEXT_HPP_INCLUDED

#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace mipmap
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	context(
		sge::opengl::info::context const &
	);

	~context()
	override;

	sge::opengl::optional_enum
	generate_mipmap_flag() const;

	typedef
	sge::opengl::fun_ref<
		PFNGLGENERATEMIPMAPPROC
	>
	gl_generate_mipmap;

	typedef
	fcppt::optional::reference<
		sge::opengl::fun_ref_value_type<
			gl_generate_mipmap
		>
	>
	optional_gl_generate_mipmap;

	typedef
	optional_gl_generate_mipmap::value_type
	gl_generate_mipmap_ref;

	optional_gl_generate_mipmap const &
	generate_mipmap() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::opengl::optional_enum const generate_mipmap_flag_;

	optional_gl_generate_mipmap const generate_mipmap_;
};

}
}
}
}

#endif
