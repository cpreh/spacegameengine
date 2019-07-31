//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_BASIC_DECL_HPP_INCLUDED
#define SGE_TIMER_BASIC_DECL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp>
#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace timer
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Clock
>
class basic final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	FCPPT_NONCOPYABLE(
		basic
	);

	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	base;
public:
	typedef
	Clock
	clock_type;

	typedef
	sge::timer::parameters<
		clock_type
	>
	parameters;

	typedef
	typename
	clock_type::time_point
	time_point;

	typedef
	typename
	clock_type::duration
	duration;

	explicit
	basic(
		parameters const &
	);

	basic(
		basic &&
	);

	basic &
	operator=(
		basic &&
	);

	~basic();

	bool
	expired() const;

	void
	expired(
		bool
	);

	bool
	active() const;

	void
	active(
		bool
	);

	duration
	interval() const;

	void
	interval(
		duration
	);

	time_point
	now() const;

	time_point
	last_time() const;

	void
	reset();
private:
	duration interval_;

	bool active_;

	bool expired_;

	time_point last_time_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
