#ifndef SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/scalar_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template<typename ValueType>
class scalar
{
FCPPT_NONCOPYABLE(
	scalar);
public:
	typedef
	ValueType
	value_type;

	scalar(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		value_type);

	void
	set(
		value_type);

	~scalar();
private:
	sge::cg::parameter::named const parameter_;
};
}
}
}

#endif
