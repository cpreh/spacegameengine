//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_OPTIONAL_NORMAL_SEQUENCE_FWD_HPP_INCLUDED
#define SGE_MODEL_MD3_OPTIONAL_NORMAL_SEQUENCE_FWD_HPP_INCLUDED

#include <sge/model/md3/normal_sequence.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::model::md3
{

using
optional_normal_sequence
=
fcppt::optional::object<
	sge::model::md3::normal_sequence
>;

}

#endif
