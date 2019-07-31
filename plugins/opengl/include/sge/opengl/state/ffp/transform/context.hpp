//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace transform
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

	typedef
	// TODO: Mesa hides this typedef
	//PFNGLLOADTRANSPOSEMATRIXFPROC
	PFNGLLOADTRANSPOSEMATRIXFARBPROC
	gl_load_transpose_matrix_proc;

	typedef
	sge::opengl::fun_ref<
		gl_load_transpose_matrix_proc
	>
	gl_load_transpose_matrix_f;

	typedef
	fcppt::optional::reference<
		sge::opengl::fun_ref_value_type<
			gl_load_transpose_matrix_f
		>
	>
	optional_load_transpose_matrix_f;

	typedef
	optional_load_transpose_matrix_f::value_type
	load_transpose_matrix_f_ref;

	optional_load_transpose_matrix_f
	load_transpose_matrix_f() const;

	bool
	have_transpose() const;

	static sge::opengl::context::id const static_id;
private:
	optional_load_transpose_matrix_f const load_transpose_matrix_f_;
};

}
}
}
}
}

#endif
