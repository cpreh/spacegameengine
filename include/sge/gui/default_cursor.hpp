#ifndef SGE_GUI_DEFAULT_CURSOR_HPP_INCLUDED
#define SGE_GUI_DEFAULT_CURSOR_HPP_INCLUDED

#include <sge/gui/cursor.hpp>
#include <sge/gui/export.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/point.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/image/loader_fwd.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL default_cursor : public cursor
{
public:
	SGE_GUI_SYMBOL default_cursor(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL point const pos() const;
	SGE_GUI_SYMBOL sge::sprite::object const sprite() const;
	SGE_GUI_SYMBOL sge::sprite::object &mutable_sprite();
	SGE_GUI_SYMBOL virtual ~default_cursor();
private:
	sge::texture::no_fragmented texture_;
	sge::sprite::object sprite_;
	sge::sprite::point const click_;
};
}
}

#endif
