/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SIGNALS_SIGNAL_HPP_INCLUDED
#define SGE_SIGNALS_SIGNAL_HPP_INCLUDED

#include <sge/signals/detail/concrete_connection.hpp>
#include <sge/signals/detail/concrete_connection_impl.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/intrusive/list.hpp>
//#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>

#define SGE_SIGNALS_DETAIL_OPERATOR_LIMIT 10

#define SGE_SIGNALS_DETAIL_DEFINE_OPERATOR(z,n,_)\
	template<\
	BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),typename T)\
	>\
	void operator()(\
		BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n),T, const &param))\
	{\
		for (typename connection_list::iterator i = connections_.begin(); i != connections_.end(); ++i)\
			i->function()(\
				BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),param));\
	}

namespace sge
{
namespace signals
{

template<typename T>
class signal : boost::noncopyable
{
public:
	typedef T function_signature;
	typedef boost::function<T> function_type;
	typedef detail::concrete_connection<
			function_signature
		> concrete_connection;
private:
	typedef boost::intrusive::list<
		concrete_connection,
		boost::intrusive::constant_time_size<
			false
		>
	> connection_list;
public:
	auto_connection connect(function_type const &f)
	{
		auto_connection a(
			new concrete_connection(f));
		connections_.push_back(static_cast<concrete_connection &>(*a));
		return a;
	}

	void operator()()
	{
		for (typename connection_list::iterator i = connections_.begin(); i != connections_.end(); ++i)\
			i->function()();
		//BOOST_FOREACH(typename connection_list::reference r,connections_)
		//	r.function()();
	}

	BOOST_PP_REPEAT(SGE_SIGNALS_DETAIL_OPERATOR_LIMIT,SGE_SIGNALS_DETAIL_DEFINE_OPERATOR,nil)
private:
	//typedef typename boost::function_traits<T>::result_type result_type;

	connection_list connections_;
};

}
}

#endif
