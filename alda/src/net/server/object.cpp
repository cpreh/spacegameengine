#include <alda/net/id.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connect_callback_fwd.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback_fwd.hpp>
#include <alda/net/server/disconnect_callback_fwd.hpp>
#include <alda/net/server/object.hpp>
#include <alda/src/net/server/detail/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/signal/auto_connection.hpp>


alda::net::server::object::object(
	alda::net::io_service_wrapper const &_io_service,
	alda::net::buffer::max_size const _buffer_max_size
)
:
	impl_(
		fcppt::make_unique_ptr<
			alda::net::server::detail::object_impl
		>(
			fcppt::ref(
				_io_service.get()
			),
			_buffer_max_size
		)
	)
{
}

alda::net::server::object::~object()
{
}

void
alda::net::server::object::listen(
	alda::net::port const _port
)
{
	return
		impl_->listen(
			_port
		);
}

alda::net::buffer::circular_send::optional_ref const
alda::net::server::object::send_buffer(
	alda::net::id const _id
)
{
	return
		impl_->send_buffer(
			_id
		);
}

alda::net::server::connection_id_container const
alda::net::server::object::connections() const
{
	return
		impl_->connections();
}

void
alda::net::server::object::queue_send(
	alda::net::id const _id
)
{
	return
		impl_->queue_send(
			_id
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_connect(
	alda::net::server::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_disconnect(
	alda::net::server::disconnect_callback const &_callback
)
{
	return
		impl_->register_disconnect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_data(
	alda::net::server::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}

void
alda::net::server::object::stop()
{
	return
		impl_->stop();
}
