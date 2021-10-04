//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_PROTOTYPE_HPP_INCLUDED
#define SGE_MODEL_OBJ_PROTOTYPE_HPP_INCLUDED

#include <sge/model/obj/box.hpp>
#include <sge/model/obj/face_vertex_sequence.hpp>
#include <sge/model/obj/material_to_face_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/texture_coordinate_sequence.hpp>
#include <sge/model/obj/vertex_coordinate_sequence.hpp>
#include <sge/model/obj/detail/symbol.hpp>
#include <sge/model/obj/material/file_sequence.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::model::obj
{
class prototype
{
	FCPPT_NONMOVABLE(
		prototype
	);
public:
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	prototype(
		fcppt::log::context_reference,
		std::filesystem::path const &
	);

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::vertex_coordinate_sequence const &
	vertex_coordinates() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::texture_coordinate_sequence const &
	texture_coordinates() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::normal_sequence const &
	normals() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::face_vertex_sequence const &
	face_vertices() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::material_to_face_sequence const &
	parts() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	std::size_t
	face_count() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::material::file_sequence const &
	material_files() const;

	[[nodiscard]]
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::box const &
	bounding_box() const;

	SGE_MODEL_OBJ_DETAIL_SYMBOL
	~prototype();
private:
	fcppt::log::object log_;
	sge::model::obj::vertex_coordinate_sequence vertex_coordinates_;
	sge::model::obj::texture_coordinate_sequence texture_coordinates_;
	sge::model::obj::normal_sequence normals_;
	sge::model::obj::face_vertex_sequence face_vertices_;
	sge::model::obj::material_to_face_sequence parts_;
	sge::model::obj::material::file_sequence material_files_;
	sge::model::obj::box bounding_box_;
};
}

#endif
