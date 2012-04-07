#include <alda/log_location.hpp>
#include <alda/net/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location const
alda::net::log_location()
{
	return
		alda::log_location()
		/
		FCPPT_TEXT("net");
}
