#ifndef SGE_THREAD_OBJECT_HPP_INCLUDED
#define SGE_THREAD_OBJECT_HPP_INCLUDED

#include <boost/thread.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace thread
{
class object
{
public:
	typedef boost::function<void ()> task;
	
	object(
		task const &);
private:
	boost::thread thread_;
};
}
}

#endif
