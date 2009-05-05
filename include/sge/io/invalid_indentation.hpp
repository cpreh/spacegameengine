#ifndef SGE_IO_INVALID_INDENTATION_HPP_INCLUDED
#define SGE_IO_INVALID_INDENTATION_HPP_INCLUDED

#include <sge/io/exception.hpp>

namespace sge
{
namespace io
{
class invalid_indentation : public exception
{
public:
	invalid_indentation(
		string const &);
};
}
}

#endif
