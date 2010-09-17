#ifndef MAJUTSU_MEMORY_FUSION_HPP_INCLUDED
#define MAJUTSU_MEMORY_FUSION_HPP_INCLUDED

#include <majutsu/memory/detail/index_of.hpp>
#include <majutsu/memory/detail/expand_fusion_initlist.hpp>
#include <majutsu/memory/detail/init_constants.hpp>
#include <majutsu/detail/find_role.hpp>
#include <majutsu/detail/make_iterators.hpp>
#include <majutsu//role_return_type.hpp>
#include <majutsu/flatten.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/for_each.hpp>

namespace majutsu
{
namespace memory
{

template<
	typename T
>
struct inner_type {
	typedef typename T::type type;
};

template<
	typename Type
>
class fusion {
public:
	typedef typename flatten<
		Type
	>::type types; // TODO

	typedef typename boost::fusion::result_of::as_vector<
		boost::mpl::transform_view<
			types,
			inner_type<
				boost::mpl::_1
			>
		>
	>::type tuple;

	fusion()
	:
		elements_()
	{
		boost::mpl::for_each<
			typename majutsu::detail::make_iterators<
				types	
			>::type
		>(
			detail::init_constants<
				fusion<
					Type
				>
			>(
				*this
			)
		);
	}

	explicit fusion(
		fusion const &other_
	)
	:
		elements_(
			other_.elements_
		)
	{}

	template<
		typename Arguments
	>
	explicit fusion(
		Arguments const &elements_
	)
	:
		elements_(
			detail::expand_fusion_initlist<
				types,
				tuple
			>(
				elements_
			)
		)
	{}

	template<
		typename Role
	>
	void
	set(
		typename majutsu::role_return_type<
			types,
			Role
		>::type const &t
	)
	{
		typedef typename majutsu::detail::find_role<
			types,
			Role
		>::type found_role;

		set_internal<
			found_role
		>(
			t
		);
	}

	template<
		typename Role
	>
	typename majutsu::role_return_type<
		types,
		Role
	>::type
	get() const
	{
		typedef typename majutsu::detail::find_role<
			types,
			Role
		>::type found_role;

		return boost::fusion::at<
			detail::index_of<
				types,
				found_role
			>
		>(
			elements_
		);
	}

	template<
		typename Iterator,
		typename Value
	>
	void
	set_internal(
		Value const &value_
	)
	{
		boost::fusion::at<
			detail::index_of<
				types,
				Iterator
			>
		>(
			elements_
		) = value_;
	}
private:
	tuple elements_;
};

}
}

#endif
