#!/bin/bash
# Example extraction and test script. Extracts all codeblocks from LaTeX files
# the source directory located in the parent directory from the script. The
# output will be stored in an examples directory relative to the current
# working directory.

# Additionally the examples will be run with G++ compiler respecting the CXX
# and CXXFLAGS environment variables. The compiler error output will be
# compared to lines in the example marked with '// error'. Any extraneous
# errors will be output on the stderr, but they will only contain the first
# line. Full error reports are in log files and in a summary.log in the wd.
# Key:
#	OK (Green) - No errors
#	OK (Green Bold) - Errors on lines marked with // error
#	OK (Yellow Bold) - Fewer errors than marked
#	OK (Red Bold) - No errors, but lines are marked.
#	FAIL (Red) - More errors than marked
#	FAIL (Red Bold) - Missing errors and more than marked

# Directory where the source latex files are.
scriptdir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# Place files into a subdirectory so we don't pollute our working copy.
mkdir -p examples
cd examples

# Extract examples from each file.
find "$scriptdir/../src" -name '*.tex' -print0 | while read -d $'\0' -r i
do
	# Files will be in the form sourcename.#.cpp
	filetemplate="\"$(basename -s .tex "$i").\"n\".cpp\""

	awk -v n=0 "/\\\\begin\\{codeblock\\}/{f=1;close($filetemplate);n++;next} /\\\\end\\{codeblock\\}/{f=0} f{print > $filetemplate}" "$i"
done

# Check compiler environment variable
if [ -z "$CXX" ]
then
	CXX=gcc
fi

# Checks log against source for missing or extraneous errors.
# Return code: bit 1 = extraneous erros, bit 2 = missing errors
function checkerrors()
{
	# Build a pattern for accepted error line numbers
	lines="\\($(grep -no '// error' "$2" | grep -o '[0-9]*' | tr '\n' '\|' | sed 's/|$//' | sed 's/|/\\|/')\\)"

	# See if any lines are absent
	allfound=1
	while read -r e
	do
		if ! grep "$2:$e:[0-9]*: \\(error:\\|sorry,\\)" "$1" > /dev/null
		then
			allfound=0
			break
		fi
	done < <(grep -no '// error' "$2" | grep -o '[0-9]*')

	# Look for excess errors
	if grep -v "$2:$lines:[0-9]*: \\(error:\\|sorry,\\)" "$1" | grep "$2:[0-9]*:[0-9]*: \\(error:\\|sorry,\\)"
	then
		if [ $allfound -eq 1 ]
		then
			return 1
		fi
		return 3
	fi

	if [ $allfound -eq 1 ]
	then
		return 0
	fi
	return 2
}

# Run examples in compiler
cd ..
find examples -name '*.cpp' -print0 | while read -d $'\0' -r i
do
	echo -n -e "\e[0;32mCompiling $i\e[0m\t[    ]"
	if $CXX -std=c++1z $CXXFLAGS -c "$i" -o /dev/null 2> "examples/$(basename -s .cpp "$i").log"
	then
		if grep '// error' "$i" > /dev/null
		then
			echo -e "\e[4D\e[1;31mOK\e[0m"
		else
			echo -e "\e[4D\e[0;32mOK\e[0m"
		fi
	else
		excess=`checkerrors "examples/$(basename -s .cpp "$i").log" "$i"`
		case $? in
			0)
				echo -e "\e[4D\e[1;32mOK\e[0m"
				;;
			1)
				echo -e "\e[5D\e[0;31mFAIL\e[0m"
				;;
			2)
				echo -e "\e[4D\e[1;33mOK\e[0m"
				;;
			3)
				echo -e "\e[5D\e[1;31mFAIL\e[0m"
				;;
		esac
		if [ ! -z "$excess" ]
		then
			echo "$excess" >&2
		fi
	fi
done

# Produce semi-organized error output
cat `find examples -name '*.log' | sort` > summary.log
