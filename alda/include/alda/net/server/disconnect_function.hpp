#ifndef ALDA_NET_SERVER_DISCONNECT_FUNCTION_HPP_INCLUDED
#define ALDA_NET_SERVER_DISCONNECT_FUNCTION_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <fcppt/string.hpp>


namespace alda
{
namespace net
{
namespace server
{

typedef void
disconnect_function(
	alda::net::id,
	fcppt::string const &
);

}
}
}

#endif
