
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

#ifndef SGE_FUNCTION_OBJECT_HPP
#define SGE_FUNCTION_OBJECT_HPP

#include <sge/function/detail/has_adressof_overload.hpp>
#include <sge/function/detail/functor_wrapper.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <tr1/functional>

namespace sge
{

namespace function
{

namespace detail
{



}

template< typename Function >
struct object;

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 0
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 1
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 2
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 3
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 4
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 5
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 6
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 7
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 8
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 9
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 10
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 11
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 12
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 13
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 14
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 15
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 16
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 17
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 18
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 19
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 20
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 21
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 22
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 23
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 24
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 25
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 26
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 27
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS

#define SGE_FUNCTION_OBJECT_PP_NUM_PARAMS 28
#include <sge/function/object_template.hpp>
#undef SGE_FUNCTION_OBJECT_PP_NUM_PARAMS
/*
template< typename R  >
struct object< R() >
{
   public:

      typedef typename std::tr1::function<R()> function_type;
      typedef R return_type;

      explicit object()
      {}

      explicit object( const object& other )
         : function_( other.function_ )
      {}
      
      // constructor for functors without operator& overload
      template< typename F >
      explicit object
         (
            F f,
            typename boost::enable_if
               <
                  typename boost::mpl::and_
                     <
                        boost::is_class< F >,
                        boost::mpl::not_
                           <
                              detail::has_addressof_overload< F >
                           >
                        >::type
                     >::type* v = 0
         )
         : function_( f )
      {}

      // constructor for functors with operator& overload
      template< typename F >
      explicit object
         (
            F f,
            typename boost::enable_if
               <
                  typename boost::mpl::and_
                     <
                        boost::is_class< F >,
                        detail::has_addressof_overload< F >
                     >::type
               >::type* v = 0
         )
         : function_( detail::functor_wrapper< F, R() >( f ) )
      {}

      // constructor for regular functions
      template< typename F >
      explicit object
                  (
                     F *f,
                     typename boost::enable_if
                        <
                           boost::mpl::and_
                              <
                                 boost::is_function<F>,
                                 boost::mpl::not_
                                    <
                                       boost::is_class<F>
                                    >
                              >
                        >::type* v = 0
                  )
         : function_( f )
      {}

      R operator() ( )
      {
         return function_( );
      }

      operator const function_type& () const
      {
         return function_;
      }

      function_type &function()
      { 
         return function_;
      }

      const function_type &function() const
      { 
         return function_;
      }

   private:

      function_type function_;
};
*/

/*
template< typename R, typename T0  >
struct object<R (T0 )>
{
   public:
      typedef R return_type;

      explicit object()
      {}

      explicit object( const object& other )
         : function_( other.function_ )
      {}

      template< typename F>
      explicit object( F f )
         : function_( f )
      {}

      explicit object( void *f )
         : function_( f )
      {}

      R operator() ( T0 t )
      {
         return function_( t );
      }

   private:
      typedef std::tr1::function<R(T0)> func;

      func function_;
};
*/

} // end namespace function

} // end namespace sge

#endif
