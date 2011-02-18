#!/bin/sh

./util/Include/Main include

./util/Include/Main src/ | grep -v plugins

./util/Include/Main SGE_:src/plugins
