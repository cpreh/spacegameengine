#ifndef ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED
#define ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{

class io_service_wrapper
{
	FCPPT_NONASSIGNABLE(
		io_service_wrapper
	);
public:
	ALDA_SYMBOL
	explicit
	io_service_wrapper(
		boost::asio::io_service &
	);

	ALDA_SYMBOL
	boost::asio::io_service &
	get() const;
private:
	boost::asio::io_service &io_service_;
};

}
}

#endif
