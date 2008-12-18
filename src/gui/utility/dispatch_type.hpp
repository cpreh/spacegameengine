#ifndef SANGUIS_DISPATCH_TYPE_HPP_INCLUDED
#define SANGUIS_DISPATCH_TYPE_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <typeinfo>

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Result, bool done = true>
struct dispatch_type_impl {
	template<
		typename Iterator,
		typename LastIterator,
		typename Fun,
		typename Type,
		typename OtherType,
		typename Handler
		>
	static Result
	execute(
		Iterator *,
		LastIterator *,
		Fun &,
		Type &t,
		OtherType &t2,
		Handler const &def_handler)
	{
		return def_handler(t,t2);
	}
};

template<typename Result>
struct dispatch_type_impl<Result, false> {
	template<
		typename Iterator,
		typename LastIterator,
		typename Fun,
		typename Type,
		typename OtherType,
		typename Handler
		>
	static Result
	execute(
		Iterator *,
		LastIterator *,
		Fun &f,
		Type &t,
		OtherType &t2,
		Handler const &def_handler)
	{
		typedef typename boost::mpl::deref<Iterator>::type item;
		typedef typename boost::mpl::next<Iterator>::type iter;

		return typeid(t) == typeid(item)
			? f(static_cast<item &>(t),t2)
			: dispatch_type_impl<
				Result,
				boost::is_same<iter, LastIterator>::value
				>::execute
				(static_cast<iter *>(0),
				 static_cast<LastIterator *>(0),
				 f,
				 t,
				 t2,
				 def_handler);
	}
};

template<
	typename Sequence,
	typename Result,
	typename Fun,
	typename Type,
	typename OtherType,
	typename Handler
	>
Result
dispatch_type(
	Fun &f,
	Type &t,
	OtherType &t2,
	Handler const &def_handler)
{
	typedef typename boost::mpl::begin<Sequence>::type first;
	typedef typename boost::mpl::end<Sequence>::type last;

	return dispatch_type_impl<
		Result,
		boost::is_same<first, last>::value >
		::execute(
			static_cast<first *>(0),
			static_cast<last *>(0),
			f,
			t,
			t2,
			def_handler);
}
}
}
}

#endif
