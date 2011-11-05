#!/bin/sh
pushd include > /dev/null
convenience_headers sge || exit -1

# remove opengl from renderer
sed -i '\@#include <sge/renderer/opengl/opengl.hpp>$@d' sge/renderer/renderer.hpp
popd > /dev/null

multi_update_license util/license_paths.json || exit -1

util/prettify_includes.sh
