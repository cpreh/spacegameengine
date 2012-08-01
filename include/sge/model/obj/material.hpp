#ifndef SGE_MODEL_OBJ_MATERIAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/texture_path.hpp>
#include <sge/renderer/material.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class material
{
public:
	SGE_MODEL_OBJ_SYMBOL
	material(
		sge::model::obj::identifier const &,
		sge::renderer::material const &,
		sge::model::obj::texture_path const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::identifier const &
	identifier() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::material const &
	renderer_material() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::texture_path const &
	texture() const;
private:
	sge::model::obj::identifier identifier_;
	sge::renderer::material renderer_material_;
	sge::model::obj::texture_path texture_;
};
}
}
}

#endif
