#include <alda/log_context.hpp>
#include <alda/src/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>


fcppt::log::parameters::object const
alda::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters::with_context(
			alda::log_context(),
			_location
		)
		.level_defaults(
			fcppt::io::clog(),
			fcppt::log::level::info
		)
		.enabled(
			true
		);
}
