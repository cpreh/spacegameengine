//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/parameters_fwd.hpp>
#include <sge/timer/clocks/parameter_fwd.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>


namespace sge
{
namespace timer
{

template<
	typename Clock
>
class parameters final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	using
	state_base
	=
	sge::timer::clocks::detail::wrapper<
		Clock
	>;
public:
	using
	clock_type
	=
	Clock;

	using
	duration
	=
	typename
	clock_type::duration;

	using
	clock_parameter
	=
	sge::timer::clocks::parameter<
		Clock
	>;

	explicit
	parameters(
		duration
	);

	parameters(
		clock_parameter,
		duration
	);

	parameters &
	active(
		bool
	);

	parameters &
	expired(
		bool
	);

	[[nodiscard]]
	duration
	interval() const;

	[[nodiscard]]
	state_base const &
	clock() const;

	[[nodiscard]]
	bool
	active() const;

	[[nodiscard]]
	bool
	expired() const;
private:
	duration interval_;

	bool active_;

	bool expired_;
};

}
}

#endif
