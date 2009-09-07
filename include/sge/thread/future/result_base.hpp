#ifndef SGE_THREAD_FUTURE_RESULT_BASE_HPP_INCLUDED
#define SGE_THREAD_FUTURE_RESULT_BASE_HPP_INCLUDED

#include <sge/noncopyable.hpp>
#include <sge/exception_ptr.hpp>

namespace sge
{
namespace thread
{
namespace future
{
class result_base
{
SGE_NONCOPYABLE(result_base)
public:
	virtual void destroy() = 0;

	exception_ptr error_;

	struct deleter
	{
		void operator()(result_base*) const;
	};
protected:
	~result_base();
};
}
}
}

#endif
