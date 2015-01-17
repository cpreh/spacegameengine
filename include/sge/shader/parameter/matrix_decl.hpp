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


#ifndef SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/shader/parameter/is_projection_matrix.hpp>
#include <sge/shader/parameter/matrix_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/matrix/static_fwd.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
class matrix
{
FCPPT_NONCOPYABLE(
	matrix);
public:
	typedef
	ValueType
	value_type;

	typedef
	fcppt::math::matrix::static_<value_type,M,N>
	matrix_type;

	static fcppt::math::size_type const rows =
		M;

	static fcppt::math::size_type const columns =
		N;

	matrix(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		sge::renderer::device::core const &,
		sge::shader::parameter::is_projection_matrix const &,
		matrix_type const &);

	void
	set(
		matrix_type const &);

	~matrix();
private:
	sge::cg::parameter::named const parameter_;
	sge::shader::parameter::is_projection_matrix const is_projection_matrix_;
};
}
}
}

#endif
