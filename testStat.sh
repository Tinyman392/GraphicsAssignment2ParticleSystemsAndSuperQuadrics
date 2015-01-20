#!/bin/bash

make -f makeStat
./stat > stat.rd
./rd_view stat.rd