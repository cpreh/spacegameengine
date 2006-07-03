#ifndef QFBOT_SCHEDULER_HPP_INCLUDED
#define QFBOT_SCHEDULER_HPP_INCLUDED

#include <queue>
#include <boost/function.hpp>

namespace qfbot
{

typedef boost::function<void ()> handler_type;
typedef unsigned long priority_type;

class priority_handler {
public:
	priority_handler(const handler_type& h, priority_type p)
		: h(h), p(p) {}
	handler_type handler() const { return h; }
	bool operator< (const priority_handler& r) const { return p < r.p; }
private:
	handler_type h;
	priority_type p;
};

class scheduler {
public:
	typedef priority_handler handler_type;

	void add_task(const handler_type& t)
	{
		requests.push(t);
	}
	void run()
	{
		while(!requests.empty())
		{
			const handler_type& req = requests.top();
			req.handler()();
			requests.pop();
		}
	}
private:
	std::priority_queue<handler_type> requests;
};

}

#endif
