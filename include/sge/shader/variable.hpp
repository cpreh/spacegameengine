#ifndef SGE_SHADER_VARIABLE_HPP_INCLUDED
#define SGE_SHADER_VARIABLE_HPP_INCLUDED

#include <sge/shader/symbol.hpp>
#include <sge/shader/value_type.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace shader
{
class variable
{
public:
	SGE_SHADER_SYMBOL explicit
	variable(
		renderer::glsl::string const &name,
		variable_type::type,
		value_type const &);

	SGE_SHADER_SYMBOL renderer::glsl::string const
	declaration() const;

	SGE_SHADER_SYMBOL variable_type::type
	type() const;

	SGE_SHADER_SYMBOL renderer::glsl::string const
	name() const;

	SGE_SHADER_SYMBOL value_type const
	initial_value() const;
private:
	renderer::glsl::string name_,declaration_;
	variable_type::type type_;
	value_type initial_value_;
};
}
}

#endif
