#include <sge/thread/future/error.hpp>
#include <sge/text.hpp>

namespace
{
sge::string code_to_string(
	sge::thread::future::error_code::type const t)
{
	switch (t)
	{
		case sge::thread::future::error_code::broken_promise:
			return SGE_TEXT("broken promise");
		case sge::thread::future::error_code::already_retrieved:
			return SGE_TEXT("already retrieved");
		case sge::thread::future::error_code::promise_already_satisfied:
			return SGE_TEXT("promise already satisfied");
	}
	return SGE_TEXT("invalid error code");
}
}

sge::thread::future::error::error(
	error_code::type const _code)
:
	sge::exception(SGE_TEXT("a future error occured: ")+code_to_string(_code)),
	code_(
		_code)
{
}

sge::thread::future::error_code::type sge::thread::future::error::code() const
{
	return code_;
}
