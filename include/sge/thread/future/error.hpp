#ifndef SGE_THREAD_FUTURE_ERROR_HPP_INCLUDED
#define SGE_THREAD_FUTURE_ERROR_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/thread/future/error_code.hpp>

namespace sge
{
namespace thread
{
namespace future
{
class error
:
	public exception
{
public:
	explicit error(
		error_code::type);
	error_code::type code() const;
private:
	error_code::type code_;
};
}
}
}

#endif
