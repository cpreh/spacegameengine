#ifndef SGE_SCENIC_SKY_DOME_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SKY_DOME_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_scoped_ptr.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/texture_manager_fwd.hpp>
#include <sge/scenic/sky/dome/latitude.hpp>
#include <sge/scenic/sky/dome/longitude.hpp>
#include <sge/scenic/sky/dome/texture_path.hpp>
#include <sge/scenic/sky/dome/y_translation.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace sky
{
namespace dome
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		sge::renderer::device &,
		sge::shader::context &,
		sge::scenic::texture_manager &,
		sge::scenic::sky::dome::texture_path const &,
		sge::camera::base &,
		sge::scenic::sky::dome::longitude const &,
		sge::scenic::sky::dome::latitude const &,
		sge::scenic::sky::dome::y_translation const &);

	void
	render(
		sge::renderer::context::object &);

	~object();
private:
	sge::scenic::sky::dome::y_translation const y_translation_;
	sge::scenic::texture_manager &texture_manager_;
	sge::scenic::sky::dome::texture_path const texture_path_;
	sge::renderer::device &renderer_;
	sge::camera::base &camera_;
	sge::renderer::vertex_declaration_scoped_ptr vertex_declaration_;
	sge::renderer::vertex_buffer_scoped_ptr vertex_buffer_;
	sge::renderer::index_buffer_scoped_ptr index_buffer_;
	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> mvp_parameter_;
	sge::shader::parameter::planar_texture texture_parameter_;
};
}
}
}
}

#endif
