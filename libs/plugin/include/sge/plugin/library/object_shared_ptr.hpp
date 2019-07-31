//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LIBRARY_OBJECT_SHARED_PTR_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_OBJECT_SHARED_PTR_HPP_INCLUDED

#include <sge/plugin/library/object_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

typedef fcppt::shared_ptr<
	sge::plugin::library::object
> object_shared_ptr;

}
}
}

#endif
