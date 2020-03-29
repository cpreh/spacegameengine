//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_CREATE_HPP_INCLUDED
#define SGE_MODEL_MD3_CREATE_HPP_INCLUDED

#include <sge/model/md3/loader_unique_ptr.hpp>
#include <sge/model/md3/detail/symbol.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge
{
namespace model
{
namespace md3
{

SGE_MODEL_MD3_DETAIL_SYMBOL
sge::model::md3::loader_unique_ptr
create(
	fcppt::log::context_reference
);

}
}
}

#endif
