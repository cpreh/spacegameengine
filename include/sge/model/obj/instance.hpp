#ifndef SGE_MODEL_OBJ_INSTANCE_HPP_INCLUDED
#define SGE_MODEL_OBJ_INSTANCE_HPP_INCLUDED

#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/group_sequence.hpp>
#include <sge/model/obj/object_sequence.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/group_name.hpp>
#include <sge/model/obj/object_name.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/tr1/unordered_map.hpp>

namespace sge
{
namespace model
{
namespace obj
{
/**
	The object loader does NOT support the following:

	- Smoothing groups: too complex to implement, requires multiple
    passes over the input
	- Materials: too complex to parse, see the spec here: http://paulbourke.net/dataformats/mtl/
	- Point primitives: too irrelevant
	- Curves: too complex, too irrelevant
 */
class instance
{
FCPPT_NONCOPYABLE(
	instance);
public:
	explicit
	instance(
		fcppt::filesystem::path const &);

	obj::vertex_sequence const
	vertices() const;

	obj::texcoord_sequence const
	texcoords() const;

	obj::normal_sequence const
	normals() const;

	obj::group_sequence const
	groups() const;

	obj::object_sequence const
	objects() const;

	obj::face_sequence const
	group_faces(
		obj::group_name const &);

	obj::face_sequence const
	object_faces(
		obj::object_name const &);
private:
	typedef
	std::tr1::unordered_map
	<
		obj::group_name,
		obj::face_sequence
	>
	group_to_faces;

	typedef
	std::tr1::unordered_map
	<
		obj::object_name,
		obj::face_sequence
	>
	object_to_faces;

	obj::vertex_sequence vertices_;
	obj::texcoord_sequence texcoords_;
	obj::normal_sequence normals_;
	obj::group_sequence groups_;
	obj::object_sequence objects_;
	group_to_faces group_to_faces_;
	object_to_faces object_to_faces_;
};
}
}
}

#endif
