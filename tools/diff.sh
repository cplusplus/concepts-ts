#!/bin/bash

old=$1
new=$2

# \providecommand{\DIFadd}[1]{\protect\cbstart{\protect\color{blue}\uwave{#1}}\protect\cbend} %DIF PREAMBLE
# \providecommand{\DIFdel}[1]{\protect\cbdelete{\protect\color{magenta}\sout{#1}}\protect\cbdelete} %DIF PREAMBLE

flags="--flatten --type CULINECHBAR --config PICTUREENV=codeblock"
latexdiff $flags $old $new
