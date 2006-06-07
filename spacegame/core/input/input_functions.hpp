#ifndef SGE_INPUT_FUNCTIONS_HPP_INCLUDED
#define SGE_INPUT_FUNCTIONS_HPP_INCLUDED

#include "./key_type.hpp"

namespace sge
{
	inline key_state key_value(const input_array& a, const key_type& t)
	{
		key_state value = 0;
		for(input_array::const_iterator it(a.begin()); it != a.end(); ++it)
			if(it->first==t)
				value = it->second;
		return value;
	}
	inline key_state key_value(const input_array& a, const key_code c)
	{
		key_state value = 0;
		for(input_array::const_iterator it(a.begin()); it != a.end(); ++it)
			if(it->first.code == c)
				value = it->second;
		return value;
	}
}

#endif

