#ifndef SGE_EXCEPTION_PTR_HPP_INCLUDED
#define SGE_EXCEPTION_PTR_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
typedef shared_ptr<exception> exception_ptr;
}

#endif
