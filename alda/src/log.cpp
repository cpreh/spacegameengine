#include <alda/log.hpp>
#include <alda/log_location.hpp>
#include <alda/src/log_parameters.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>


SGE_LOG_DECLARE_LIB_BASE(
	alda::log,
	alda::log_parameters(
		alda::log_location()
	)
)
