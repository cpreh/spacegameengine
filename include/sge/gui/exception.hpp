#ifndef SGE_GUI_EXCEPTION_HPP_INCLUDED
#define SGE_GUI_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace gui
{
class exception : public sge::exception
{
public:
	exception(string const &);
};
}
}

#endif
