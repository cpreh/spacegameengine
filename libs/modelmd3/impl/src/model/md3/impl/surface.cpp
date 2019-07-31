//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/load_flags_field.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/max_qpath.hpp>
#include <sge/model/md3/impl/read_and_check_id3p.hpp>
#include <sge/model/md3/impl/read_s32.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <sge/model/md3/impl/s32.hpp>
#include <sge/model/md3/impl/shader.hpp>
#include <sge/model/md3/impl/shader_vector.hpp>
#include <sge/model/md3/impl/surface.hpp>
#include <sge/model/md3/impl/texpos.hpp>
#include <sge/model/md3/impl/texpos_vector.hpp>
#include <sge/model/md3/impl/transformed_vertex.hpp>
#include <sge/model/md3/impl/transformed_vertex_vector.hpp>
#include <sge/model/md3/impl/triangle.hpp>
#include <sge/model/md3/impl/triangle_vector.hpp>
#include <sge/model/md3/impl/vertex.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::surface::surface(
	std::istream &_stream,
	sge::model::md3::load_flags_field const _flags,
	sge::model::md3::impl::surface::num_frames const _num_frames_head
)
:
	// TODO: Direct initialization
	name_(),
	shaders_(),
	triangles_(),
	texpos_(),
	transformed_vertices_()
{
	std::istream::off_type const start(
		_stream.tellg()
	);

	if(
		!sge::model::md3::impl::read_and_check_id3p(
			_stream
		)
	)
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("Invalid md3 surface!")
			);

	name_ =
		sge::model::md3::impl::read_string<
			sge::model::md3::impl::max_qpath::value
		>(
			_stream
		);

	// flags
	sge::model::md3::impl::read_s32(
		_stream
	);

	sge::model::md3::impl::s32 const frames(
		sge::model::md3::impl::read_s32(
			_stream
		)
	);

	if(
		frames
		!=
		_num_frames_head.get()
	)
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("num_frames mismatch in md3::impl::surface!")
			);

	sge::model::md3::impl::s32 const
		num_shaders(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		num_verts(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		num_triangles(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		ofs_triangles(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		ofs_shaders(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		ofs_st(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		ofs_xyznormal(
			sge::model::md3::impl::read_s32(
				_stream
			)
		),
		ofs_end(
			sge::model::md3::impl::read_s32(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_triangles
		,
		std::ios_base::beg
	);

	// TODO: map
	for(
		s32 i = 0;
		i < num_triangles;
		++i
	)
		triangles_.push_back(
			sge::model::md3::impl::triangle(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_shaders
		,
		std::ios_base::beg
	);

	// TODO: map
	for(
		s32 i = 0;
		i < num_shaders;
		++i
	)
		shaders_.push_back(
			sge::model::md3::impl::shader(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_st
		,
		std::ios_base::beg
	);

	// TODO: map
	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		texpos_.push_back(
			sge::model::md3::impl::texpos(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_xyznormal
		,
		std::ios_base::beg
	);

	// TODO: map
	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		transformed_vertices_.push_back(
			sge::model::md3::impl::transformed_vertex(
				sge::model::md3::impl::vertex(
					_stream,
					_flags
				)
			)
		);

	_stream.seekg(
		start
		+
		ofs_end
		,
		std::ios_base::beg
	);
}

sge::model::md3::string const &
sge::model::md3::impl::surface::name() const
{
	return
		name_;
}

sge::model::md3::impl::shader_vector const &
sge::model::md3::impl::surface::shaders() const
{
	return
		shaders_;
}

sge::model::md3::impl::triangle_vector const &
sge::model::md3::impl::surface::triangles() const
{
	return
		triangles_;
}

sge::model::md3::impl::texpos_vector const &
sge::model::md3::impl::surface::texpos() const
{
	return
		texpos_;
}

sge::model::md3::impl::transformed_vertex_vector const &
sge::model::md3::impl::surface::transformed_vertices() const
{
	return
		transformed_vertices_;
}
