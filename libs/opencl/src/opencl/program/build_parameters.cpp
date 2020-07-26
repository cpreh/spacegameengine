//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/program/build_options.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <sge/opencl/program/optional_notification_callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opencl::program::build_parameters::build_parameters()
:
	devices_(),
	build_options_(),
	notification_callback_()
{
}

sge::opencl::program::build_parameters
sge::opencl::program::build_parameters::devices(
	sge::opencl::device::object_ref_sequence &&_devices
) &&
{
	devices_ =
		optional_object_ref_sequence(
			std::move(
				_devices
			)
		);

	return
		std::move(
			*this
		);
}

sge::opencl::program::build_parameters
sge::opencl::program::build_parameters::options(
	sge::opencl::program::build_options &&_build_options
) &&
{
	build_options_ =
		std::move(
			_build_options
		);

	return
		std::move(
			*this
		);
}

sge::opencl::program::build_parameters
sge::opencl::program::build_parameters::notification_callback(
	sge::opencl::program::notification_callback &&_notification_callback
) &&
{
	notification_callback_ =
		sge::opencl::program::optional_notification_callback{
			std::move(
				_notification_callback
			)
		};

	return
		std::move(
			*this
		);
}

sge::opencl::program::build_parameters::optional_object_ref_sequence const &
sge::opencl::program::build_parameters::devices() const
{
	return
		devices_;
}

sge::opencl::program::build_options const &
sge::opencl::program::build_parameters::build_options() const
{
	return
		build_options_;
}

sge::opencl::program::optional_notification_callback const &
sge::opencl::program::build_parameters::notification_callback() const
{
	return
		notification_callback_;
}
