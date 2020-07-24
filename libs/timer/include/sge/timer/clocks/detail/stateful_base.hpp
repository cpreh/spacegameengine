//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_DETAIL_STATEFUL_BASE_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DETAIL_STATEFUL_BASE_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{
namespace detail
{

template<
	typename Clock
>
class stateful_base
{
public:
	using
	clock_ref
	=
	fcppt::reference<
		Clock const
	>;

	explicit
	stateful_base(
		clock_ref const _clock
	)
	:
		clock_(
			_clock
		)
	{
	}

	[[nodiscard]]
	Clock const &
	clock_base() const
	{
		return
			clock_.get();
	}
private:
	clock_ref clock_;
};

}
}
}
}

#endif
