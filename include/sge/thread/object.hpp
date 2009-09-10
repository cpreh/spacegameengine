#ifndef SGE_THREAD_OBJECT_HPP_INCLUDED
#define SGE_THREAD_OBJECT_HPP_INCLUDED

#include <sge/export.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

namespace sge
{
namespace thread
{
class SGE_CLASS_SYMBOL object
{
public:
	typedef boost::function<void ()> task;
	
	SGE_SYMBOL object(
		task const &);
	void join();
	SGE_SYMBOL ~object();
private:
	boost::thread thread_;
};
}
}

#endif // SGE_THREAD_OBJECT_HPP_INCLUDED
