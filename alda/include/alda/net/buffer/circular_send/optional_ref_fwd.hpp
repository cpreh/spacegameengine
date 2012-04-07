#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_OPTIONAL_REF_FWD_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

typedef fcppt::optional<
	alda::net::buffer::circular_send::object &
> optional_ref;

}
}
}
}

#endif
