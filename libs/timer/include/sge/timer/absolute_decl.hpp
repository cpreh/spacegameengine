//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED
#define SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED

#include <sge/timer/absolute_fwd.hpp>
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
class absolute final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	FCPPT_NONCOPYABLE(
		absolute
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
	typename
	clock_type::time_point
	time_point;

	typedef
	typename
	clock_type::duration
	duration;

	absolute();

	explicit
	absolute(
		Clock const &
	);

	time_point
	now() const;

	time_point
	last_time() const;

	void
	reset();
private:
	time_point last_time_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
