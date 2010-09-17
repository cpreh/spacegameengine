#ifndef MAJUTSU_DETAIL_COPY_SUBELEMENTS_HPP_INCLUDED
#define MAJUTSU_DETAIL_COPY_SUBELEMENTS_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/contains.hpp>

namespace majutsu
{
namespace detail
{

template<
	typename DestClass,
	typename SrcClass
>
class copy_subelements
{
public:
	explicit copy_subelements(
		DestClass &dest_,
		SrcClass const &src_
	)
	:
		dest_(dest_),
		src_(src_)
	{}

	typedef void result_type;

	template<
		typename Src
	>
	typename boost::enable_if<
		boost::mpl::contains<
			typename DestClass::memory_type::types,
			Src
		>,
		result_type
	>::type
	operator()(
		Src &
	) const
	{
		typedef typename Src::alias alias;

		dest_. template set<
			alias
		>(
			src_. template get<
				alias
			>()
		);
	}

	template<
		typename Src
	>
	typename boost::disable_if<
		boost::mpl::contains<
			typename DestClass::memory_type::types,
			Src
		>,
		result_type
	>::type
	operator()(
		Src &
	) const
	{
	}
private:
	DestClass &dest_;

	SrcClass const &src_;
};

}
}

#endif
