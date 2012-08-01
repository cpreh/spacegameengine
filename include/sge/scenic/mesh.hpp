#ifndef SGE_SCENIC_MESH_HPP_INCLUDED
#define SGE_SCENIC_MESH_HPP_INCLUDED

#include <sge/model/obj/instance_fwd.hpp>
#include <sge/scenic/position.hpp>
#include <sge/scenic/rotation.hpp>
#include <sge/scenic/scale.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace scenic
{
class mesh
{
FCPPT_NONCOPYABLE(
	mesh);
public:
	SGE_SCENIC_SYMBOL
	mesh(
		sge::model::obj::instance &,
		sge::scenic::position const &,
		sge::scenic::rotation const &,
		sge::scenic::scale const &);

	SGE_SCENIC_SYMBOL
	sge::model::obj::instance &
	model() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::position const &
	position() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::rotation const &
	rotation() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::scale const &
	scale() const;

	SGE_SCENIC_SYMBOL
	~mesh();
private:

};
}
}

#endif
