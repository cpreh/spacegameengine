#ifndef SGE_SHADER_EXCEPTION_HPP_INCLUDED
#define SGE_SHADER_EXCEPTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/exception.hpp>
#include <sge/shader/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace shader
{
class SGE_CLASS_SYMBOL exception
:
	public sge::exception
{
public:
	SGE_SHADER_SYMBOL
	explicit
	exception(
		fcppt::string const &);
};
}
}

#endif
