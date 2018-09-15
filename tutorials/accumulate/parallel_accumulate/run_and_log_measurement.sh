#!/bin/sh

echo 'System information :'
uname -a

echo '----------------------Optimized program performance----------------------'
./parallel_accumulate_optimized -s
./parallel_accumulate_optimized -p

echo '----------------------Unoptimized program performance----------------------'
./parallel_accumulate_unoptimized -s
./parallel_accumulate_unoptimized -p

