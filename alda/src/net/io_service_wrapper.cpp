#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/config/external_end.hpp>


alda::net::io_service_wrapper::io_service_wrapper(
	boost::asio::io_service &_io_service
)
:
	io_service_(
		_io_service
	)
{
}

boost::asio::io_service &
alda::net::io_service_wrapper::get() const
{
	return io_service_;
}
