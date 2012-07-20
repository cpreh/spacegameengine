#ifndef SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/static.hpp>


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

	typedef typename
	fcppt::math::vector::static_<ValueType,N>::type
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
