/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/rgba8.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <mizuiro/color/init/red.hpp>
#include <mizuiro/color/init/green.hpp>
#include <mizuiro/color/init/blue.hpp>
#include <mizuiro/color/init/alpha.hpp>

#define SGE_DEFINE_COLOR_A(name, r, g, b, a)\
sge::image::color::any::object const \
sge::image::colors::name()\
{\
	typedef sge::image::color::rgba8 color_type;\
	typedef color_type::format::channel_type value_type;\
\
	return \
		sge::image::color::any::object(\
			sge::image::color::rgba8(\
				(mizuiro::color::init::red = static_cast<value_type>(r))\
				(mizuiro::color::init::green = static_cast<value_type>(g))\
				(mizuiro::color::init::blue = static_cast<value_type>(b))\
				(mizuiro::color::init::alpha = static_cast<value_type>(a))\
			)\
		);\
}

#define SGE_DEFINE_COLOR(name, r, g, b)\
SGE_DEFINE_COLOR_A(name, r, g, b, 255)

SGE_DEFINE_COLOR(aliceblue,          240, 248, 255)
SGE_DEFINE_COLOR(antiquewhite,       250, 235, 215)
SGE_DEFINE_COLOR(aqua                ,0  , 255, 255)
SGE_DEFINE_COLOR(aquamarine          ,127, 255, 212)
SGE_DEFINE_COLOR(azure               ,240, 255, 255)
SGE_DEFINE_COLOR(beige               ,245, 245, 220)
SGE_DEFINE_COLOR(bisque              ,255, 228, 196)
SGE_DEFINE_COLOR(black               ,  0,   0,   0)
SGE_DEFINE_COLOR(blanchedalmond      ,255, 235, 205)
SGE_DEFINE_COLOR(blue                ,  0,   0, 255)
SGE_DEFINE_COLOR(blueviolet          ,138,  43, 226)
SGE_DEFINE_COLOR(brown               ,165,  42,  42)
SGE_DEFINE_COLOR(burlywood           ,222, 184, 135)
SGE_DEFINE_COLOR(cadetblue           , 95, 158, 160)
SGE_DEFINE_COLOR(chartreuse          ,127, 255,   0)
SGE_DEFINE_COLOR(chocolate           ,210, 105,  30)
SGE_DEFINE_COLOR(coral               ,255, 127,  80)
SGE_DEFINE_COLOR(cornflowerblue      ,100, 149, 237)
SGE_DEFINE_COLOR(cornsilk            ,255, 248, 220)
SGE_DEFINE_COLOR(crimson             ,220,  20,  60)
SGE_DEFINE_COLOR(cyan                ,  0, 255, 255)
SGE_DEFINE_COLOR(darkblue            ,  0,   0, 139)
SGE_DEFINE_COLOR(darkcyan            ,  0, 139, 139)
SGE_DEFINE_COLOR(darkgoldenrod       ,184, 134,  11)
SGE_DEFINE_COLOR(darkgray            ,169, 169, 169)
SGE_DEFINE_COLOR(darkgreen           ,  0, 100,   0)
SGE_DEFINE_COLOR(darkgrey            ,169, 169, 169)
SGE_DEFINE_COLOR(darkkhaki           ,189, 183, 107)
SGE_DEFINE_COLOR(darkmagenta         ,139,   0, 139)
SGE_DEFINE_COLOR(darkolivegreen      , 85, 107,  47)
SGE_DEFINE_COLOR(darkorange          ,255, 140,   0)
SGE_DEFINE_COLOR(darkorchid          ,153,  50, 204)
SGE_DEFINE_COLOR(darkred             ,139,   0,   0)
SGE_DEFINE_COLOR(darksalmon          ,233, 150, 122)
SGE_DEFINE_COLOR(darkseagreen        ,143, 188, 143)
SGE_DEFINE_COLOR(darkslateblue       , 72,  61, 139)
SGE_DEFINE_COLOR(darkslategray       , 47,  79,  79)
SGE_DEFINE_COLOR(darkslategrey       , 47,  79,  79)
SGE_DEFINE_COLOR(darkturquoise       ,  0, 206, 209)
SGE_DEFINE_COLOR(darkviolet          ,148,   0, 211)
SGE_DEFINE_COLOR(deeppink            ,255,  20, 147)
SGE_DEFINE_COLOR(deepskyblue         ,  0, 191, 255)
SGE_DEFINE_COLOR(dimgray             ,105, 105, 105)
SGE_DEFINE_COLOR(dimgrey             ,105, 105, 105)
SGE_DEFINE_COLOR(dodgerblue          , 30, 144, 255)
SGE_DEFINE_COLOR(firebrick           ,178,  34,  34)
SGE_DEFINE_COLOR(floralwhite         ,255, 250, 240)
SGE_DEFINE_COLOR(forestgreen         , 34, 139,  34)
SGE_DEFINE_COLOR(fuchsia             ,255,   0, 255)
SGE_DEFINE_COLOR(gainsboro           ,220, 220, 220)
SGE_DEFINE_COLOR(ghostwhite          ,248, 248, 255)
SGE_DEFINE_COLOR(gold                ,255, 215,   0)
SGE_DEFINE_COLOR(goldenrod           ,218, 165,  32)
SGE_DEFINE_COLOR(gray                ,128, 128, 128)
SGE_DEFINE_COLOR(green               ,  0, 128,   0)
SGE_DEFINE_COLOR(greenyellow         ,173, 255,  47)
SGE_DEFINE_COLOR(grey                ,128, 128, 128)
SGE_DEFINE_COLOR(honeydew            ,240, 255, 240)
SGE_DEFINE_COLOR(hotpink             ,255, 105, 180)
SGE_DEFINE_COLOR(indianred           ,205,  92,  92)
SGE_DEFINE_COLOR(indigo              , 75,   0, 130)
SGE_DEFINE_COLOR(ivory               ,255, 255, 240)
SGE_DEFINE_COLOR(khaki               ,240, 230, 140)
SGE_DEFINE_COLOR(lavender            ,230, 230, 250)
SGE_DEFINE_COLOR(lavenderblush       ,255, 240, 245)
SGE_DEFINE_COLOR(lawngreen           ,124, 252,   0)
SGE_DEFINE_COLOR(lemonchiffon        ,255, 250, 205)
SGE_DEFINE_COLOR(lightblue           ,173, 216, 230)
SGE_DEFINE_COLOR(lightcoral          ,240, 128, 128)
SGE_DEFINE_COLOR(lightcyan           ,224, 255, 255)
SGE_DEFINE_COLOR(lightgoldenrodyellow,250, 250, 210)
SGE_DEFINE_COLOR(lightgray           ,211, 211, 211)
SGE_DEFINE_COLOR(lightgreen          ,144, 238, 144)
SGE_DEFINE_COLOR(lightgrey           ,211, 211, 211)
SGE_DEFINE_COLOR(lightpink           ,255, 182, 193)
SGE_DEFINE_COLOR(lightsalmon         ,255, 160, 122)
SGE_DEFINE_COLOR(lightseagreen       , 32, 178, 170)
SGE_DEFINE_COLOR(lightskyblue        ,135, 206, 250)
SGE_DEFINE_COLOR(lightslategray      ,119, 136, 153)
SGE_DEFINE_COLOR(lightslategrey      ,119, 136, 153)
SGE_DEFINE_COLOR(lightsteelblue      ,176, 196, 222)
SGE_DEFINE_COLOR(lightyellow         ,255, 255, 224)
SGE_DEFINE_COLOR(lime                ,  0, 255,   0)
SGE_DEFINE_COLOR(limegreen           , 50, 205,  50)
SGE_DEFINE_COLOR(linen               ,250, 240, 230)
SGE_DEFINE_COLOR(magenta             ,255,   0, 255)
SGE_DEFINE_COLOR(maroon              ,128,   0,   0)
SGE_DEFINE_COLOR(mediumaquamarine    ,102, 205, 170)
SGE_DEFINE_COLOR(mediumblue          ,  0,   0, 205)
SGE_DEFINE_COLOR(mediumorchid        ,186,  85, 211)
SGE_DEFINE_COLOR(mediumpurple        ,147, 112, 219)
SGE_DEFINE_COLOR(mediumseagreen      , 60, 179, 113)
SGE_DEFINE_COLOR(mediumslateblue     ,123, 104, 238)
SGE_DEFINE_COLOR(mediumspringgreen   ,  0, 250, 154)
SGE_DEFINE_COLOR(mediumturquoise     , 72, 209, 204)
SGE_DEFINE_COLOR(mediumvioletred     ,199,  21, 133)
SGE_DEFINE_COLOR(midnightblue        , 25,  25, 112)
SGE_DEFINE_COLOR(mintcream           ,245, 255, 250)
SGE_DEFINE_COLOR(mistyrose           ,255, 228, 225)
SGE_DEFINE_COLOR(moccasin            ,255, 228, 181)
SGE_DEFINE_COLOR(navajowhite         ,255, 222, 173)
SGE_DEFINE_COLOR(navy                ,  0,   0, 128)
SGE_DEFINE_COLOR(oldlace             ,253, 245, 230)
SGE_DEFINE_COLOR(olive               ,128, 128,   0)
SGE_DEFINE_COLOR(olivedrab           ,107, 142,  35)
SGE_DEFINE_COLOR(orange              ,255, 165,   0)
SGE_DEFINE_COLOR(orangered           ,255,  69,   0)
SGE_DEFINE_COLOR(orchid              ,218, 112, 214)
SGE_DEFINE_COLOR(palegoldenrod       ,238, 232, 170)
SGE_DEFINE_COLOR(palegreen           ,152, 251, 152)
SGE_DEFINE_COLOR(paleturquoise       ,175, 238, 238)
SGE_DEFINE_COLOR(palevioletred       ,219, 112, 147)
SGE_DEFINE_COLOR(papayawhip          ,255, 239, 213)
SGE_DEFINE_COLOR(peachpuff           ,255, 218, 185)
SGE_DEFINE_COLOR(peru                ,205, 133,  63)
SGE_DEFINE_COLOR(pink                ,255, 192, 203)
SGE_DEFINE_COLOR(plum                ,221, 160, 221)
SGE_DEFINE_COLOR(powderblue          ,176, 224, 230)
SGE_DEFINE_COLOR(purple              ,128,   0, 128)
SGE_DEFINE_COLOR(red                 ,255,   0,   0)
SGE_DEFINE_COLOR(rosybrown           ,188, 143, 143)
SGE_DEFINE_COLOR(royalblue           , 65, 105, 225)
SGE_DEFINE_COLOR(saplebrown          ,139,  69,  19)
SGE_DEFINE_COLOR(salmon              ,250, 128, 114)
SGE_DEFINE_COLOR(sandybrown          ,244, 164,  96)
SGE_DEFINE_COLOR(seagreen            , 46, 139,  87)
SGE_DEFINE_COLOR(seashell            ,255, 245, 238)
SGE_DEFINE_COLOR(sienna              ,160,  82,  45)
SGE_DEFINE_COLOR(silver              ,192, 192, 192)
SGE_DEFINE_COLOR(skyblue             ,135, 206, 235)
SGE_DEFINE_COLOR(slateblue           ,106,  90, 205)
SGE_DEFINE_COLOR(slategray           ,112, 128, 144)
SGE_DEFINE_COLOR(slategrey           ,112, 128, 144)
SGE_DEFINE_COLOR(snow                ,255, 250, 250)
SGE_DEFINE_COLOR(springgreen         ,  0, 255, 127)
SGE_DEFINE_COLOR(steelblue           , 70, 130, 180)
SGE_DEFINE_COLOR(tan                 ,210, 180, 140)
SGE_DEFINE_COLOR(teal                ,  0, 128, 128)
SGE_DEFINE_COLOR(thistle             ,216, 191, 216)
SGE_DEFINE_COLOR(tomato              ,255,  99,  71)
SGE_DEFINE_COLOR(turquoise           , 64, 224, 208)
SGE_DEFINE_COLOR(violet              ,238, 130, 238)
SGE_DEFINE_COLOR(wheat               ,245, 222, 179)
SGE_DEFINE_COLOR(white               ,255, 255, 255)
SGE_DEFINE_COLOR(whitesmoke          ,245, 245, 245)
SGE_DEFINE_COLOR(yellow              ,255, 255,   0)
SGE_DEFINE_COLOR(yellowgreen         ,154, 205,  50)

SGE_DEFINE_COLOR_A(transparent       ,  0,   0,   0, 0)

#undef SGE_DEFINE_COLOR
#undef SGE_DEFINE_COLOR_A
