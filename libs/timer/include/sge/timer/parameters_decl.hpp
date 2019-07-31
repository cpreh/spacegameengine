//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/parameters_fwd.hpp>
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
	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	state_base;
public:
	typedef
	Clock
	clock_type;

	typedef
	typename
	clock_type::duration
	duration;

	explicit
	parameters(
		duration
	);

	parameters(
		clock_type const &,
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

	duration
	interval() const;

	state_base const &
	clock() const;

	bool
	active() const;

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
