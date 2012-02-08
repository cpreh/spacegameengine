#include <sge/opengl/cocoa/SGECocoaOpenGLView.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/get.hpp>
#include <vector>

@implementation SGECocoaOpenGLView
{
	@private
	NSOpenGLContext *context_;
}

- (SGECocoaOpenGLView *)initWithFrame:(NSRect)f andParameters:(sge::renderer::parameters const &)p
{
	if(fcppt::variant::holds_type<sge::renderer::display_mode>(p.screen_mode()))
		throw
			sge::renderer::exception(
				FCPPT_TEXT("Sorry, fullscreen isn't supported on Mac OSX"));

	std::vector<NSOpenGLPixelFormatAttribute> attributes;

	attributes.push_back(
		NSOpenGLPFADoubleBuffer);

	attributes.push_back(
		NSOpenGLPFAColorSize);

	// Here, we rely on the fact that the constants in the visual_depth enum
	// correspond to the numeric value of the depth.
	attributes.push_back(
		fcppt::variant::get<sge::renderer::visual_depth::type>(p.screen_mode()));

	switch(p.depth_stencil_buffer())
	{
		case sge::renderer::depth_stencil_buffer::off:
			break;
		case sge::renderer::depth_stencil_buffer::d16:
			attributes.push_back(
				NSOpenGLPFADepthSize);
			attributes.push_back(
				16);
			break;
		case sge::renderer::depth_stencil_buffer::d24:
			attributes.push_back(
				NSOpenGLPFADepthSize);
			attributes.push_back(
				24);
			break;
		case sge::renderer::depth_stencil_buffer::d32:
			attributes.push_back(
				NSOpenGLPFADepthSize);
			attributes.push_back(
				32);
			break;
		case sge::renderer::depth_stencil_buffer::d24s8:
			attributes.push_back(
				NSOpenGLPFADepthSize);
			attributes.push_back(
				24);
			attributes.push_back(
				NSOpenGLPFAStencilSize);
			attributes.push_back(
				8);
			break;
	}

	attributes.push_back(
		0);

    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:&attributes[0]];
	
    if ([super initWithFrame:f]) 
	{
        context_ = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
		[context_ makeCurrentContext];
	}
    return self;
}

- (void)beginRendering
{
	[context_ clearDrawable];
	[context_ setView:self];
    [context_ makeCurrentContext];
}

- (void)swapBuffers
{
	[context_ flushBuffer];
	[NSOpenGLContext clearCurrentContext];
}

@end
