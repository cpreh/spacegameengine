//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/timer/basic_impl.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sge::timer::frames_counter::frames_counter()
:
	timer_(
		sge::timer::parameters<
			clock
		>(
			std::chrono::seconds(
				1
			)
		)
	),
	current_frames_(
		0
	),
	display_frames_(
		0
	)
{
}

void
sge::timer::frames_counter::update()
{
	++current_frames_;

	if(
		sge::timer::reset_when_expired(
			fcppt::make_ref(
				timer_
			)
		)
	)
	{
		display_frames_ = current_frames_;

		current_frames_ = 0;
	}
}

sge::timer::frames_counter::counter
sge::timer::frames_counter::frames() const
{
	return
		display_frames_;
}

fcppt::string
sge::timer::frames_counter::frames_str() const
{
	return
		fcppt::output_to_fcppt_string(
			this->frames()
		);
}

sge::timer::frames_counter::~frames_counter()
= default;
