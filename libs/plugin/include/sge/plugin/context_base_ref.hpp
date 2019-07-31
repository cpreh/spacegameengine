//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CONTEXT_BASE_REF_HPP_INCLUDED
#define SGE_PLUGIN_CONTEXT_BASE_REF_HPP_INCLUDED

#include <sge/plugin/context_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace plugin
{

typedef
fcppt::reference<
	sge::plugin::context_base
>
context_base_ref;

}
}

#endif
