#ifndef MAJUTSU_MEMORY_DETAIL_INIT_RAW_MEMORY_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_RAW_MEMORY_HPP_INCLUDED

#include <fcppt/nonassignable.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/mpl/at.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Memory
>
class init_raw_memory
{
	FCPPT_NONASSIGNABLE(
		init_raw_memory
	)
public:
	explicit init_raw_memory(
		Memory &memory_
	)
	:
		memory_(memory_)
	{}

	template<
		typename Pair
	>
	void
	operator()(
		Pair const &pair
	) const
	{
		memory_. template set_internal<
			typename boost::mpl::at_c<
				Pair,
				1
			>::type
		>(
			boost::fusion::at_c<
				0
			>(
				pair
			)
		);
	}
private:
	Memory &memory_;
};

}
}
}

#endif
