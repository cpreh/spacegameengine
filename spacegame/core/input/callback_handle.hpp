#ifndef SGE_CALLBACK_HANDLE_HPP_INCLUDED
#define SGE_CALLBACK_HANDLE_HPP_INCLUDED

#include <boost/signals/connection.hpp>
#include "../main/shared_ptr.hpp"

namespace sge
{

class callback_handle_impl {
public:
	callback_handle_impl(const boost::signals::connection& con)
		: con(con)
	{}
	~callback_handle_impl()
	{
		con.disconnect();
	}
private:
	boost::signals::connection con;
};

typedef shared_ptr<callback_handle_impl> callback_handle;

}

#endif
