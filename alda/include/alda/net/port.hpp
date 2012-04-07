#ifndef ALDA_NET_PORT_HPP_INCLUDED
#define ALDA_NET_PORT_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>


namespace alda
{
namespace net
{

// unsigned int is big enough for all ipv4 ports
FCPPT_MAKE_STRONG_TYPEDEF(
	unsigned int,
	port
);

}
}

#endif
