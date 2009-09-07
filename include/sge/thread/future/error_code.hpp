#ifndef SGE_THREAD_FUTURE_ERROR_CODE_HPP_INCLUDED
#define SGE_THREAD_FUTURE_ERROR_CODE_HPP_INCLUDED

namespace sge
{
namespace thread
{
namespace future
{
namespace error_code
{
enum type
{
	broken_promise,
	already_retrieved,
	promise_already_satisfied
};
}
}
}
}

#endif
