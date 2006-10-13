/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_FUNCTIONAL_HPP_INCLUDED
#define SGE_FUNCTIONAL_HPP_INCLUDED

#include <functional>

namespace sge
{

template<typename NewArg1, typename NewArg2, typename Fun> 
	class binary_dereference_binder : public std::binary_function<NewArg1,NewArg2,typename Fun::result_type> { 
public: 
	binary_dereference_binder(const Fun& f) 
		: f(f) {} 
	typename Fun::result_type operator()(NewArg1 arg1, NewArg2 arg2) const { return f(*arg1,*arg2); } 
private: 
	Fun f; 
}; 
 
template<typename NewArg1, typename Fun> 
	class unary_dereference_binder : public std::unary_function<NewArg1,typename Fun::result_type> { 
public: 
	unary_dereference_binder(const Fun& f) 
		: f(f) {} 
	typename Fun::result_type operator()(NewArg1 arg) const { return t(*arg); } 
private: 
	Fun f; 
}; 
 
template<typename NewArg1, typename NewArg2, typename Fun> 
	binary_dereference_binder<NewArg1,NewArg2,Fun> dereference_binder(const Fun& f) 
{ 
	return binary_dereference_binder<NewArg1,NewArg2,Fun>(f); 
} 
 
template<typename NewArg1, typename Fun> 
	unary_dereference_binder<NewArg1,Fun> dereference_binder(const Fun& f) 
{ 
	 return unary_dereference_binder<NewArg1,Fun>(f); 
} 

}

#endif
