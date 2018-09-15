#!/bin/sh

echo '[System information]\n'
uname -a
echo '\n'

echo '----------------------Optimized program performance----------------------'
./parallel_accumulate_optimized -s
echo '\n'
./parallel_accumulate_optimized -p
echo '\n'

echo '----------------------Unoptimized program performance----------------------'
./parallel_accumulate_unoptimized -s
echo '\n'
./parallel_accumulate_unoptimized -p
echo '\n'

