
#include <sge/function/object.hpp>

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>

#include <iostream>

#include <cassert>

struct functor1
{
   void operator() () {
   std::cout << "functor1" << std::endl;
   }
};

struct functor2
{
   void operator() () {
   std::cout << "functor2" << std::endl;
   }

   float operator&() {}
};

struct functor3
{
   int operator() () {
   std::cout << "functor3" << std::endl;

   return 5;
   }

};

struct functor4
{
   int operator() ( int ) {
   std::cout << "functor4" << std::endl;

   return 7;
   }

};

void function1()
{
   std::cout << "function1" << std::endl;
}


int main()
{
   functor1 f1;
   functor2 f2;
   functor3 f3;
   functor4 f4;

   sge::function::object< void ()     > f_1( f1 );
   sge::function::object< void ()     > f_2( f2 );
   sge::function::object< void ()     > f_3( function1 );
   sge::function::object< int  ()     > f_4( f3 );
   sge::function::object< int ( int ) > f_5( f4 );

   f_1();
   f_2();
   f_3();

   std::cout << f_4() << std::endl;
   std::cout << f_5( 7 ) << std::endl;


   //bool b = true; function<void ()>(phoenix::ref(b) = false)(); assert(b == false);

   bool b = true;  sge::function::object<void()>( boost::phoenix::ref(b) = false )(); assert( b == false );
   //bool b = true;  std::tr1::function<void()>( boost::phoenix::ref(b) = false )(); assert( b == false );
}
