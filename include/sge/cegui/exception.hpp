#ifndef SGE_CEGUI_EXCEPTION_HPP_INCLUDED
#define SGE_CEGUI_EXCEPTION_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/exception.hpp>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL exception
:
	public fcppt::exception
{
public:
	SGE_CEGUI_SYMBOL explicit 
	exception(
		fcppt::string const &);

	SGE_CEGUI_SYMBOL virtual ~exception() throw();
};
}
}

#endif
