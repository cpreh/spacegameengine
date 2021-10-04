//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_PART_NAME_SEQUENCE_HPP_INCLUDED
#define SGE_MODEL_MD3_PART_NAME_SEQUENCE_HPP_INCLUDED

#include <sge/model/md3/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::model::md3
{

using
part_name_sequence
=
std::vector<
	sge::model::md3::string
>;

}

#endif
