//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_DELTA_DECL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DELTA_DECL_HPP_INCLUDED

#include <sge/timer/clocks/delta_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{

template<
	typename Duration
>
class delta
{
	FCPPT_NONCOPYABLE(
		delta
	);
public:
	typedef
	typename
	Duration::rep
	rep;

	typedef
	typename
	Duration::period
	period;

	typedef
	Duration
	duration;

	typedef
	std::chrono::time_point<
		delta
	>
	time_point;

	static
	bool const is_steady =
		true;

	delta();

	~delta();

	void
	update(
		duration const &
	);

	time_point
	now() const;
private:
	time_point now_;
};

}
}
}

#endif
