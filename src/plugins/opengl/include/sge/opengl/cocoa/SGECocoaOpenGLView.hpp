#ifndef SGE_OPENGL_COCOA_SGECOCOAOPENGLVIEW_HPP_INCLUDED
#define SGE_OPENGL_COCOA_SGECOCOAOPENGLVIEW_HPP_INCLUDED

#include <sge/renderer/parameters_fwd.hpp>
#import <Cocoa/Cocoa.h>

@interface SGECocoaOpenGLView : NSView

- (SGECocoaOpenGLView *)initWithFrame:(NSRect)f andParameters:(sge::renderer::parameters const &)p;
- (void)beginRendering;
- (void)swapBuffers;

@end

#endif

