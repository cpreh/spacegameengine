/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


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
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context()
	override;

	typedef
	sge::opengl::fun_ref<
		PFNGLLOADTRANSPOSEMATRIXFPROC
	>
	gl_load_transpose_matrix_f;

	typedef
	fcppt::optional<
		gl_load_transpose_matrix_f
	>
	optional_load_transpose_matrix_f;

	optional_load_transpose_matrix_f const
	load_transpose_matrix_f() const;

	bool
	have_transpose() const;

	typedef void parameter;

	static sge::opengl::context::system::id const static_id;
private:
	optional_load_transpose_matrix_f const load_transpose_matrix_f_;
};

}
}
}
}
}

#endif
