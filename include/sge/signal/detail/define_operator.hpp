#ifndef SGE_SIGNAL_DETAIL_DEFINE_OPERATOR_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_DEFINE_OPERATOR_HPP_INCLUDED

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define SGE_SIGNAL_DETAIL_DEFINE_EMPTY_OPERATOR\
	result_type operator()()\
	{\
		result_type t = result_type();\
		for (typename connection_list::iterator i = base::connections().begin();\
		     i != base::connections().end();\
				 ++i)\
			t = combiner_(i->function()(),t);\
		return t;\
	}

#define SGE_SIGNAL_DETAIL_DEFINE_OPERATOR(z,n,_)\
	template<\
	BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),typename T)\
	>\
	result_type operator()(\
		BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n),T, const &param))\
	{\
		result_type t = result_type();\
		for (typename connection_list::iterator i = base::connections().begin();\
		     i != base::connections().end();\
				 ++i)\
			t = combiner_(\
				t,\
				i->function()(\
					BOOST_PP_ENUM_PARAMS_Z(z,BOOST_PP_INC(n),param)));\
		return t;\
	}

#endif
