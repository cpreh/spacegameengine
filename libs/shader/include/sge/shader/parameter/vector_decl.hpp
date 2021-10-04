//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/vector_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge::shader::parameter
{

template<
	typename ValueType,
	fcppt::math::size_type N
>
class vector
{
	FCPPT_NONMOVABLE(
		vector
	);
public:
	using
	value_type
	=
	ValueType;

	using
	vector_type
	=
	fcppt::math::vector::static_<
		ValueType,
		N
	>;

	static constexpr fcppt::math::size_type const size =
		N;

	vector(
		sge::cg::program::object_ref,
		sge::shader::parameter::name const &,
		vector_type const &
	);

	void
	set(
		vector_type const &
	);

	~vector(); // NOLINT(performance-trivially-destructible)
private:
	sge::cg::parameter::named const parameter_;
};

}

#endif
