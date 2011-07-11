#ifndef SGE_MODEL_OBJ_FACE_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_HPP_INCLUDED

#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace model
{
namespace obj
{
class face
{
public:
	typedef
	std::vector<vertex_sequence::size_type>
	vertex_indices;

	typedef
	std::vector<texcoord_sequence::size_type>
	texcoord_indices;

	typedef
	std::vector<normal_sequence::size_type>
	normal_indices;

	typedef
	fcppt::optional<texcoord_indices>
	optional_texcoord_indices;

	typedef
	fcppt::optional<normal_indices>
	optional_normal_indices;

	vertex_indices const &
	vertices() const;

	optional_texcoord_indices const &
	texcoords() const;

	optional_normal_indices const &
	normals() const;
private:
	vertex_indices vertices_;
	optional_texcoord_indices texcoords_;
	optional_normal_indices normals_;
};
}
}
}

#endif
