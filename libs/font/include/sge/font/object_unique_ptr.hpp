//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_FONT_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace font
{

typedef
fcppt::unique_ptr<
	sge::font::object
>
object_unique_ptr;

}
}

#endif
