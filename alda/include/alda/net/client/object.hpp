#ifndef ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED
#define ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED

#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <alda/net/client/connect_callback_fwd.hpp>
#include <alda/net/client/data_callback_fwd.hpp>
#include <alda/net/client/error_callback_fwd.hpp>
#include <alda/net/client/object_fwd.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace alda
{
namespace net
{
namespace client
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		alda::net::parameters const &
	);

	~object();

	void
	connect(
		alda::net::host const &,
		alda::net::port
	);

	void
	disconnect();

	alda::net::buffer::circular_send::object &
	send_buffer();

	void
	queue_send();

	fcppt::signal::auto_connection
	register_connect(
		alda::net::client::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_error(
		alda::net::client::error_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		alda::net::client::data_callback const &
	);
private:
	fcppt::scoped_ptr<
		alda::net::client::detail::object_impl
	> const impl_;
};

}
}
}

#endif
