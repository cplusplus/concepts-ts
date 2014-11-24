#!/bin/bash

old=$1
new=$2

flags="--flatten --config PICTUREENV=codeblock"
latexdiff $flags $old $new
