#ifndef MAJUTSU_MEMORY_DETAIL_INIT_CONSTANTS_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_CONSTANTS_HPP_INCLUDED

#include <majutsu/is_constant.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/utility/enable_if.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Memory
>
class init_constants
{
	FCPPT_NONASSIGNABLE(
		init_constants
	)
public:
	explicit init_constants(
		Memory &mem_
	)
	:
		mem_(mem_)
	{}

	template<
		typename Iterator
	>
	typename boost::enable_if<
		majutsu::is_constant<
			typename boost::mpl::deref<
				Iterator
			>::type
		>,
		void
	>::type
	operator()(
		Iterator &
	) const
	{
		typedef typename boost::mpl::deref<
			Iterator
		>::type type;

		mem_. template set_internal<
			Iterator
		>(
			type::value
		);
	}

	template<
		typename Iterator
	>
	typename boost::disable_if<
		majutsu::is_constant<
			typename boost::mpl::deref<
				Iterator
			>::type
		>,
		void
	>::type
	operator()(
		Iterator &
	) const
	{}
private:
	Memory &mem_;
};

}
}
}

#endif
