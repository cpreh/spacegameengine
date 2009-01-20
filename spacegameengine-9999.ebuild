# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games git

DESCRIPTION="A portable, easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"

EGIT_REPO_URI="git://freundlich.mine.nu/spacegameengine.git"

LICENSE="LGPL-2"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE="bullet devil dga mad narrowstring openal opengl test truetype vorbis wave x11input"

DEPEND="${RDEPEND}
        >=dev-util/cmake-2.6
        dev-util/pkgconfig"
RDEPEND=">=dev-libs/boost-1.35
         x11-libs/libX11
         virtual/libc
		 bullet? ( sci-physics/bullet )
         devil? ( media-libs/devil )
		 mad? ( media-libs/libmad )
         openal? ( media-libs/openal )
         opengl? (
             media-libs/glew
			 x11-libs/libXrandr
             x11-libs/libXxf86vm )
         truetype? ( media-libs/freetype )
         x11input? ( dga? ( x11-libs/libXxf86dga ) )
         vorbis? ( media-libs/libvorbis )"

src_unpack() {
	git_src_unpack
	cd ${S}
}

src_compile() {
	local myconf=""

	use bullet && myconf="${myconf} -D ENABLE_BULLET:=1"
	use devil && myconf="${myconf} -D ENABLE_DEVIL:=1"
	use dga && myconf="${myconf} -D ENABLE_DGA:=1"
	use mad && myconf="${myconf} -D ENABLE_MAD:=1"
	use narrowstring && myconf="${myconf} -D ENABLE_NARROW_STRING:=1"
	use opengl && myconf="${myconf} -D ENABLE_OPENGL:=1"
	use openal && myconf="${myconf} -D ENABLE_OPENAL:=1"
	use test && myconf="${myconf} -D ENABLE_TEST:=1"
	use truetype && myconf="${myconf} -D ENABLE_FREETYPE:=1"
	use vorbis && myconf="${myconf} -D ENABLE_VORBIS:=1"
	use wave && myconf="${myconf} -D ENABLE_WAVE:=1"
	use x11input && myconf="${myconf} -D ENABLE_X11INPUT:=1"

	mkdir build
	cd build

	cmake ${myconf} \
		-DCMAKE_C_FLAGS="${CFLAGS}" \
		-DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
		-DCMAKE_INSTALL_PREFIX=/usr \
		.. || die "cmake failed"

	emake || die "emake failed"
}

src_install() {
	cd build
	emake DESTDIR=${D} install || die "emake install failed"
}
