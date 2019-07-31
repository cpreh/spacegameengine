//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_ADJUSTABLE_DECL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_ADJUSTABLE_DECL_HPP_INCLUDED

#include <sge/timer/clocks/adjustable_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{
template<typename ClockImpl>
class adjustable
{
FCPPT_NONCOPYABLE(
	adjustable);
public:
	typedef typename
	ClockImpl::rep
	rep;

	typedef typename
	ClockImpl::period
	period;

	typedef typename
	ClockImpl::duration
	duration;

	typedef typename
	ClockImpl::time_point
	time_point;

	typedef
	float
	float_type;

	static bool const is_steady =
		true;

	adjustable();

	~adjustable();

	void
	update();

	float_type
	factor() const;

	void
	factor(
		float_type);

	time_point
	now() const;
private:
	time_point current_time_;
	time_point transformed_time_;
	float_type factor_;
};
}
}
}

#endif
