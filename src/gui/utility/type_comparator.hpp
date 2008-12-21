#ifndef SGE_GUI_UTILITY_TYPE_COMPARATOR_HPP_INCLUDED
#define SGE_GUI_UTILITY_TYPE_COMPARATOR_HPP_INCLUDED

#include <typeinfo>
#include <boost/mpl/for_each.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/if.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
template<
	typename Obj,
	typename Callback>
struct type_comparator_impl
{
	public:
	type_comparator_impl(
		Obj &obj,
		Callback &cb,
		unsigned &count)
		: obj(obj),
			cb(cb),
			count(count)
	{ 
		count = 0; 
	}
	
	template<typename U>
	void operator()(U &)
	{
		if (typeid(U) != typeid(obj))
			return;

		++count;
		/*cb(
			dynamic_cast<typename boost::mpl::if_<boost::is_const<Obj>,U const,U>::type &>(obj));*/
	//	cb(static_cast<U &>(obj));
		/*
			dynamic_cast<
				typename boost::mpl::if_<
					boost::is_const<Obj>,
						typename boost::add_reference< 
							typename boost::add_const<U>::type >::type,
						typename boost::add_reference<U>::type >::type>(
					obj));
						*/
	}

	private:
	Obj &obj;
	Callback &cb;
	unsigned &count;
};

template<
	typename Types,
	typename Obj,
	typename Callback,
	typename Fallback>
typename Callback::result_type type_comparator(
	Obj &obj,
	Callback &cb,
	//Fallback fb)
	Fallback)
{
	unsigned count;
	boost::mpl::for_each<Types>(
		type_comparator_impl<Obj,Callback>(
			obj,
			cb,
			count));
	//if (!count)
	//	return fb(obj);
	return cb.value();
}
}
}
}

#endif
