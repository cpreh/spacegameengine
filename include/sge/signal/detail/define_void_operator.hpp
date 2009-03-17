#ifndef SGE_SIGNAL_DETAIL_DEFINE_VOID_OPERATOR_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_DEFINE_VOID_OPERATOR_HPP_INCLUDED

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define SGE_SIGNAL_DETAIL_DEFINE_EMPTY_VOID_OPERATOR\
	void operator()()\
	{\
		for (typename connection_list::iterator i = base::connections().begin();\
		     i != base::connections().end();\
				 ++i)\
			i->function()();\
	}

#define SGE_SIGNAL_DETAIL_DEFINE_VOID_OPERATOR(z,n,_)\
	template<\
	BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),typename T)\
	>\
	void operator()(\
		BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n),T, const &param))\
	{\
		for (typename connection_list::iterator i = base::connections().begin();\
		     i != base::connections().end();\
				 ++i)\
			i->function()(\
				BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),param));\
	}

#endif
