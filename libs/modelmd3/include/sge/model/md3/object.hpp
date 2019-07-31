//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_OBJECT_HPP_INCLUDED
#define SGE_MODEL_MD3_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/object_fwd.hpp>
#include <sge/model/md3/optional_normal_sequence.hpp>
#include <sge/model/md3/optional_texcoord_sequence.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/texcoord_sequence.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/model/md3/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace model
{
namespace md3
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_MODEL_MD3_DETAIL_SYMBOL
	object();
public:
	virtual
	sge::model::md3::index_sequence
	indices(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::vertex_sequence
	vertices(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::optional_texcoord_sequence
	texcoords(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::optional_normal_sequence
	normals(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::part_name_sequence
	part_names() const = 0;

	SGE_MODEL_MD3_DETAIL_SYMBOL
	virtual
	~object();
};

}
}
}

#endif
