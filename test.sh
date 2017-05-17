#!/bin/sh
export DYLD_LIBRARY_PATH="/Users/dchristo/8_2017/Malloc"
export DYLD_INSERT_LIBRARIES="/Users/dchristo/8_2017/Malloc/libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE="1"
$@
