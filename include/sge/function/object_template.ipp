
/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2009 Thomas Heller (thom.heller@gmail.com)

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

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#ifndef SGE_FUNCTION_OBJECT_HPP
#error "This file is not a standalone header"
#endif

#define SGE_FUNCTION_OBJECT_PP_TEMPLATE_PARAMS \
   typename R BOOST_PP_COMMA_IF( SGE_FUNCTION_OBJECT_PP_NUM_PARAMS ) \
   BOOST_PP_ENUM_PARAMS( SGE_FUNCTION_OBJECT_PP_NUM_PARAMS, typename T )

#define SGE_FUNCTION_OBJECT_PP_TEMPLATE_ARGS \
   R( BOOST_PP_ENUM_PARAMS( SGE_FUNCTION_OBJECT_PP_NUM_PARAMS, T ) )

#define SGE_FUNCTION_OBJECT_PP_FUNCTION_OPERATOR \
   R operator() ( SGE_FUNCTION_OBJECT_PP_FUNCTION_PARAMS )

#define SGE_FUNCTION_OBJECT_PP_FUNCTION_PARAMS \
   BOOST_PP_ENUM_BINARY_PARAMS( SGE_FUNCTION_OBJECT_PP_NUM_PARAMS, T, t )

#define SGE_FUNCTION_OBJECT_PP_FUNCTION_ARGS \
   BOOST_PP_ENUM_PARAMS( SGE_FUNCTION_OBJECT_PP_NUM_PARAMS, t )

namespace sge
{

namespace function
{

template< SGE_FUNCTION_OBJECT_PP_TEMPLATE_PARAMS  >
struct object< SGE_FUNCTION_OBJECT_PP_TEMPLATE_ARGS >
{
   private:
      /// This class is used to implement the safe_bool idiom.
      struct hidden_type_
      {
	hidden_type_* m_bool_;
      };

      /// This typedef is used to implement the safe_bool idiom.
      typedef hidden_type_* hidden_type_::* safe_bool_;

   public:

      typedef typename std::tr1::function< SGE_FUNCTION_OBJECT_PP_TEMPLATE_ARGS > function_type;
      typedef R return_type;

      explicit object()
      {}

      object( const object& other )
         : function_( other.function_ )
      {}
      
      // constructor for functors without operator& overload, and regular functions
      template< typename F >
      object
         (
            F f,
            typename boost::enable_if
               <
                  boost::mpl::not_
                     <
                        detail::has_addressof_overload< F >
                     >
               >::type* = 0
         )
         : function_( f )
      {}

      // constructor for functors with operator& overload
      template< typename F >
      object
         (
            F f,
            typename boost::enable_if
               <
                  boost::mpl::and_
                     <
                        boost::is_class< F >,
                        detail::has_addressof_overload< F >
                     >
               >::type* = 0
         )
         : function_( detail::functor_wrapper< F, SGE_FUNCTION_OBJECT_PP_TEMPLATE_ARGS >( f ) )
      {}

      SGE_FUNCTION_OBJECT_PP_FUNCTION_OPERATOR
      {
         return function_( SGE_FUNCTION_OBJECT_PP_FUNCTION_ARGS );
      }
      
      SGE_FUNCTION_OBJECT_PP_FUNCTION_OPERATOR const
      {
         return function_( SGE_FUNCTION_OBJECT_PP_FUNCTION_ARGS );
      }

      operator safe_bool_() const
      {
         if( function_ )
            return &hidden_type_::m_bool_;
         else
            return 0;
      }

   private:

      function_type function_;
};

} // end namespace function

} // end namespace sge

#undef SGE_FUNCTION_OBJECT_PP_TEMPLATE_PARAMS
#undef SGE_FUNCTION_OBJECT_PP_TEMPLATE_ARGS
#undef SGE_FUNCTION_OBJECT_PP_FUNCTION_PARAMS
#undef SGE_FUNCTION_OBJECT_PP_FUNCTION_ARGS
#undef SGE_FUNCTION_OBJECT_PP_FUNCTION_OPERATOR
