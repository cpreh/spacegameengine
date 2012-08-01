#ifndef SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/image2d/loader_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
class texture_manager
{
FCPPT_NONCOPYABLE(
	texture_manager);
public:
	SGE_SCENIC_SYMBOL
	texture_manager(
		sge::renderer::device &,
		sge::image2d::system &);

	SGE_SCENIC_SYMBOL
	sge::renderer::texture::planar &
	texture_for_path(
		boost::filesystem::path const &);

	SGE_SCENIC_SYMBOL
	~texture_manager();
private:
	typedef
	boost::ptr_map
	<
		boost::filesystem::path,
		sge::renderer::texture::planar
	>
	path_to_texture_map;

	sge::renderer::device &renderer_;
	sge::image2d::system &image_loader_;
	path_to_texture_map path_to_texture_;
};
}
}

#endif
