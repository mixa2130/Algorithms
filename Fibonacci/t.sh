#!/bin/bash

app="apps/s"
limit="2s"

if [ "$#" -ne 0 ]; then
	app=$1
fi

app="timeout $limit ./$app"

echo "$app"

counter=0
total=0
timeouts=0
errors=0
for f in tests/*.in
do
	let total++
	echo -n "$f... "

	#out="$(cat $f | $app | sed 's/^ *//;s/ *$//')"
	out="$(cat $f | $app)"
	status=$?;
	out=$(echo "$out" | sed 's/^ *//;s/ *$//')

	valid="$(cat ${f%.*}.out | sed 's/^ *//;s/ *$//')"
	if [ "$out" == "$valid" ]; then
		echo "OK"
		let counter++
	elif [ "$status" == "124" ]; then
		echo "TIMEOUT"
		let timeouts++
	else
		echo "FAILED"
		let errors++
	fi
done
echo "Passed: $counter of $total. Timeouts: $timeouts, errors: $errors"
