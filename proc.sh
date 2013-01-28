#!/bin/sh

for _var in `seq -w 1000`
do
    ./main &
done
