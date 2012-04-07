#include <alda/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>


fcppt::log::location const
alda::log_location()
{
	return
		fcppt::log::location(
			FCPPT_TEXT("alda")
		);
}
