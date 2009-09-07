#include <sge/thread/future/result_base.hpp>

void sge::thread::future::result_base::deleter::operator()(result_base * const r) const
{
	r->destroy();
}

sge::thread::future::result_base::~result_base()
{
}
