//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_OBJECT_BASE_HOOK_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_OBJECT_BASE_HOOK_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace detail
{

typedef
boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
>
object_base_hook;

}
}
}
}

#endif
