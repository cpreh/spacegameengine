//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template
<
	typename ValueType,
	fcppt::math::size_type N
>
class vector
{
FCPPT_NONCOPYABLE(
	vector);
public:
	typedef
	ValueType
	value_type;

	typedef
	fcppt::math::vector::static_<ValueType,N>
	vector_type;

	static fcppt::math::size_type const size =
		N;

	vector(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		vector_type const &);

	void
	set(
		vector_type const &);

	~vector();
private:
	sge::cg::parameter::named const parameter_;
};
}
}
}

#endif
