#include <sge/scenic/render_context/mesh.hpp>

namespace
{
template<typename T>
T
set_bits(
	T const begin,
	T const size,
	T const value,
	T const input)
{
	T const part =
		((1u << begin) - 1u) ^ ((1u << (begin + size)) - 1u);

	return
		(input & ~part) | (value << begin);
}

sge::scenic::render_context::sort_index
create_sort_index(
	sge::scenic::render_context::index_type const _material,
	sge::scenic::render_context::index_type const _vertex_buffer,
	sge::scenic::render_context::index_type const _texture)
{
	return
		set_bits<sge::scenic::render_context::sort_index>(
			3u,
			20u,
			static_cast<sge::scenic::render_context::sort_index>(
				_material),
			set_bits<sge::scenic::render_context::sort_index>(
				//23u,
				43u,
				20u,
				static_cast<sge::scenic::render_context::sort_index>(
					_vertex_buffer),
				set_bits<sge::scenic::render_context::sort_index>(
					//43u,
					23u,
					20u,
					static_cast<sge::scenic::render_context::sort_index>(
						_texture),
					0u)));
}
}

sge::scenic::render_context::mesh::mesh(
	sge::scenic::render_context::index_type const _material,
	sge::scenic::render_context::index_type const _vertex_buffer,
	sge::scenic::render_context::index_type const _texture,
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index_buffer &_index_buffer,
	sge::model::obj::index_buffer_range const &_index_buffer_range)
:
	material_(
		_material),
	vertex_buffer_(
		_vertex_buffer),
	texture_(
		_texture),
	sort_index_(
		create_sort_index(
			_material,
			_vertex_buffer,
			_texture)),
	modelview_(
		_modelview),
	index_buffer_(
		&_index_buffer),
	index_buffer_range_(
		_index_buffer_range)
{

}

sge::scenic::render_context::index_type
sge::scenic::render_context::mesh::material() const
{
	return
		material_;
}

sge::scenic::render_context::index_type
sge::scenic::render_context::mesh::vertex_buffer() const
{
	return
		vertex_buffer_;
}

sge::scenic::render_context::index_type
sge::scenic::render_context::mesh::texture() const
{
	return
		texture_;
}

sge::renderer::matrix4 const &
sge::scenic::render_context::mesh::modelview() const
{
	return
		modelview_;
}

sge::renderer::index_buffer &
sge::scenic::render_context::mesh::index_buffer() const
{
	return
		*index_buffer_;
}

sge::model::obj::index_buffer_range const &
sge::scenic::render_context::mesh::index_buffer_range() const
{
	return
		index_buffer_range_;
}
