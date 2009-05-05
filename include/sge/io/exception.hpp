#ifndef SGE_IO_EXCEPTION_HPP_INCLUDED
#define SGE_IO_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>

namespace sge
{
namespace io
{
class exception : public sge::exception
{
public:
	exception(string const &);
};
}
}

#endif
