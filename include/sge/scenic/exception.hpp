#ifndef SGE_SCENIC_EXCEPTION_HPP_INCLUDED
#define SGE_SCENIC_EXCEPTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/exception.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace scenic
{
class exception
:
	public sge::exception
{
public:
	SGE_SCENIC_SYMBOL
	explicit
	exception(
		fcppt::string const &);
};
}
}

#endif
