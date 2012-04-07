#ifndef ALDA_NET_SERVER_DISCONNECT_CALLBACK_FWD_HPP_INCLUDED
#define ALDA_NET_SERVER_DISCONNECT_CALLBACK_FWD_HPP_INCLUDED

#include <alda/net/server/disconnect_function.hpp>
#include <fcppt/function/object_fwd.hpp>


namespace alda
{
namespace net
{
namespace server
{

typedef fcppt::function::object<
	alda::net::server::disconnect_function
> disconnect_callback;

}
}
}

#endif
