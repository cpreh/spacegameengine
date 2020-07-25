//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_ENTITY_HPP_INCLUDED
#define SGE_SCENIC_SCENE_ENTITY_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/mesh_path.hpp>
#include <sge/scenic/scene/position.hpp>
#include <sge/scenic/scene/rotation.hpp>
#include <sge/scenic/scene/scale.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{

class entity
{
	FCPPT_NONCOPYABLE(
		entity
	);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	entity(
		sge::scenic::scene::mesh_path &&,
		sge::scenic::scene::position,
		sge::scenic::scene::rotation,
		sge::scenic::scene::scale
	);

	SGE_SCENIC_DETAIL_SYMBOL
	entity(
		entity &&
	)
	noexcept;

	SGE_SCENIC_DETAIL_SYMBOL
	entity &
	operator=(
		entity &&
	)
	noexcept;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::mesh_path const &
	mesh_path() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::position const &
	position() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::rotation const &
	rotation() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::scale const &
	scale() const;

	SGE_SCENIC_DETAIL_SYMBOL
	~entity();
private:
	sge::scenic::scene::mesh_path mesh_path_;
	sge::scenic::scene::position position_;
	sge::scenic::scene::rotation rotation_;
	sge::scenic::scene::scale scale_;
};

}
}
}

#endif
