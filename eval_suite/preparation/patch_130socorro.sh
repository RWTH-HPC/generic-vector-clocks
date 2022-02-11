#!/usr/local_rwth/bin/zsh
#
# Downloads 130.socorro patch and unpacks it to SPEC directory.
#

set -e

FILE_NAME=socorro_patch.tar.bz2
SPEC_DIR=`grep spec ../config | cut -d ' ' -f 2`

echo "Download patch..."
curl -s -S http://www.specbench.org/mpi2007/src.alt/mpi2007-socorro-nullify_ptr-1202022.tar.bz2 --output $FILE_NAME

echo "Patching socorro in $SPEC_DIR..."
tar -xvf $FILE_NAME -C $SPEC_DIR

rm $FILE_NAME
