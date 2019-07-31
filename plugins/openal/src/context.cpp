//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/alc.hpp>
#include <sge/openal/context.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/funcs/alc_create_context.hpp>
#include <sge/openal/funcs/alc_destroy_context.hpp>


sge::openal::context::context(
	sge::openal::device &_device
)
:
	device_(
		_device
	),
	context_(
		sge::openal::funcs::alc_create_context(
			device_.aldevice()
		)
	)
{
}

ALCcontext &
sge::openal::context::alcontext()
{
	return
		*context_;
}

ALCdevice &
sge::openal::context::aldevice()
{
	return
		device_.aldevice();
}

sge::openal::context::~context()
{
	sge::openal::funcs::alc_destroy_context(
		this->aldevice(),
		this->alcontext()
	);
}
