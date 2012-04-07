#ifndef ALDA_SRC_NET_SERVER_DETAIL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_SRC_NET_SERVER_DETAIL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/optional_ref_fwd.hpp>
#include <alda/net/server/connect_callback_fwd.hpp>
#include <alda/net/server/connect_function.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback_fwd.hpp>
#include <alda/net/server/data_function.hpp>
#include <alda/net/server/disconnect_callback_fwd.hpp>
#include <alda/net/server/disconnect_function.hpp>
#include <alda/net/server/detail/connection_container.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>
#include <alda/net/server/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

class object_impl
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	object_impl(
		boost::asio::io_service &,
		alda::net::buffer::max_size
	);

	~object_impl();

	void
	listen(
		alda::net::port
	);

	alda::net::buffer::circular_send::optional_ref const
	send_buffer(
		alda::net::id
	);

	alda::net::server::connection_id_container const
	connections() const;

	void
	queue_send(
		alda::net::id
	);

	fcppt::signal::auto_connection
	register_connect(
		alda::net::server::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		alda::net::server::disconnect_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		alda::net::server::data_callback const &
	);

	void
	stop();
private:
	boost::asio::io_service &io_service_;

	alda::net::buffer::max_size const buffer_max_size_;

	boost::asio::ip::tcp::acceptor acceptor_;

	alda::net::id::value_type id_counter_;

	fcppt::unique_ptr<
		alda::net::server::detail::connection
	> new_connection_;

	alda::net::server::detail::connection_container connections_;

	fcppt::signal::object<
		alda::net::server::connect_function
	> connect_signal_;

	fcppt::signal::object<
		alda::net::server::disconnect_function
	> disconnect_signal_;

	fcppt::signal::object<
		alda::net::server::data_function
	> data_signal_;

	void
	accept();

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t,
		alda::net::server::detail::connection &
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t,
		alda::net::server::detail::connection &
	);

	void
	accept_handler(
		boost::system::error_code const &
	);

	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &,
		alda::net::server::detail::connection const &
	);

	void
	send_data(
		alda::net::server::detail::connection &
	);

	void
	receive_data(
		alda::net::server::detail::connection &
	);

	alda::net::server::detail::connection &
	connection(
		alda::net::id
	);
};

}
}
}
}

#endif
