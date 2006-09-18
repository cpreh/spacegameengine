# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games

DESCRIPTION="A portable easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"
SRC_URI="http://spacegameengine.sourceforge.net/${P}.tar.bz2"

LICENSE="GPL"
SLOT="0"
KEYWORDS="~x86"
IUSE="opengl truetype devil xinput"

DEPEND="${RDEPEND}
        scons"
RDEPEND="dev-libs/boost
         x11-libs/libX11
		 sys-libs/glibc
		 media-fonts/corefonts
		 ogl? (
		 	media-libs/glew
			x11-libs/libXxf86vm )
         devil? ( media-libs/devil )
		 truetype? ( media-libs/freetype )
		 xinput? ( x11-libs/libXxf86dga )"

src_unpack() {
	unpack ${A}
	cd ${S}
}

src_compile() {
	scons ${MAKEOPTS} prefix=/usr workdir=${WORKDIR} libdir=$(get_libdir) || die
}

src_install() {
	scons install prefix=/usr workdir=${WORKDIR} libdir=$(get_libdir) || die
	# scons is too gay
	insinto /usr/include/spacegame
	doins core/main/*.hpp
	insinto /usr/include/spacegame/renderer
	doins core/renderer/*.hpp
	insinto /usr/include/spacegame/input
	doins core/input/*.hpp
	insinto /usr/include/spacegame/font
	doins core/font/*.hpp
	insinto /usr/include/spacegame/image
	doins core/image/*.hpp
	insinto /usr/include/spacegame/sprite
	doins core/sprite/*.hpp
	insinto /usr/include/spacegame/math
	doins core/math/*.hpp
	insinto /usr/include/spacegame/gui
	doins gui/*.hpp

	insinto /usr/share/games/spacegame/mainskin
	doins media/mainskin/*.png

	exeinto /usr/bin
	doexe sgetest

	insinto /usr/$(get_libdir)/spacegame/
	doins ${WORKDIR}/usr/$(get_libdir)/spacegame/*.so

	insinto /usr/$(get_libdir)/
	doins ${WORKDIR}/usr/$(get_libdir)/*.so
}
