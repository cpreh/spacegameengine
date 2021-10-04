//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/shader/parameter/is_projection_matrix.hpp>
#include <sge/shader/parameter/matrix_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/math/matrix/static_fwd.hpp>


namespace sge::shader::parameter
{

template<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
class matrix
{
	FCPPT_NONMOVABLE(
		matrix
	);
public:
	using
	value_type
	=
	ValueType;

	using
	matrix_type
	=
	fcppt::math::matrix::static_<
		value_type,
		M,
		N
	>;

	static constexpr fcppt::math::size_type const rows =
		M;

	static constexpr fcppt::math::size_type const columns =
		N;

	matrix(
		sge::cg::program::object_ref,
		sge::shader::parameter::name const &,
		sge::renderer::device::core const &,
		sge::shader::parameter::is_projection_matrix const &,
		matrix_type const &
	);

	void
	set(
		matrix_type const &
	);

	~matrix(); // NOLINT(performance-trivially-destructible)
private:
	sge::cg::parameter::named const parameter_;

	sge::shader::parameter::is_projection_matrix const is_projection_matrix_;
};

}

#endif
