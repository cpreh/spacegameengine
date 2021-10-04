//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_SURFACE_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_SURFACE_HPP_INCLUDED

#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/s32.hpp>
#include <sge/model/md3/impl/shader_vector.hpp>
#include <sge/model/md3/impl/texpos_vector.hpp>
#include <sge/model/md3/impl/transformed_vertex_vector.hpp>
#include <sge/model/md3/impl/triangle_vector.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge::model::md3::impl
{

class surface
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::model::md3::impl::s32,
		num_frames
	);

	surface(
		std::istream &,
		sge::model::md3::load_flags_field,
		num_frames
	);

	[[nodiscard]]
	sge::model::md3::string const &
	name() const;

	[[nodiscard]]
	sge::model::md3::impl::shader_vector const &
	shaders() const;

	[[nodiscard]]
	sge::model::md3::impl::triangle_vector const &
	triangles() const;

	[[nodiscard]]
	sge::model::md3::impl::texpos_vector const &
	texpos() const;

	[[nodiscard]]
	sge::model::md3::impl::transformed_vertex_vector const &
	transformed_vertices() const;
private:
	sge::model::md3::string name_;

	sge::model::md3::impl::shader_vector shaders_;

	sge::model::md3::impl::triangle_vector triangles_;

	sge::model::md3::impl::texpos_vector texpos_;

	sge::model::md3::impl::transformed_vertex_vector transformed_vertices_;
};

}

#endif
