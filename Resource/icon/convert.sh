#!/bin/bash

for file in $(ls)
do
	cfile=${file/png/jpg}
	convert ${file} ${cfile}
done


