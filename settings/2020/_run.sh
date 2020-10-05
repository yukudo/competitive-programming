#!/bin/bash

#
# 使い方
#     _run.sh B    => g++ B.cpp && ./a < B.in.txt
#     _run.sh B -d => g++ B.cpp && ./a < B.in.txt | diff -b -B - B.out.txt
#     _run.sh B -s => ./_submit.sh B
#     _run.sh B -gen => (run B_gen.cpp to create B.stress.in.txt and B.stress.out.txt)
#     _run.sh B -stress => g++ B.cpp && ./a < B.stress.in.txt
#     _run.sh B -stress -d => g++ B.cpp && ./a < B.stress.in.txt | diff -b -B - B.stress.out.txt
#

readonly COMPILE_CMD='c++oj'

function doit() {
  cmd="$1"
  echo "$cmd" 1>&2
  eval $cmd
}

# 自分の環境専用だからいいのだ
shopt -s expand_aliases
alias c++oj='g++ -std=c++14 -O2 -Wall -Wno-unused-result -Winit-self -I . -DLOCAL=1'

diff_flg=0
submit_flg=0
stress_flg=0
generate_flg=0
for OPT in "$@"; do
  case $OPT in
  '-d' | '--diff' ) diff_flg=1 ;;
  '-s' | '--submit') submit_flg=1 ;;
  '-stress' | '--stress') stress_flg=1 ;;
  '-gen' | '--gen') generate_flg=1 ;;
  * ) [[ -z "${task_id+x}" ]] && task_id=$1 ;;
  esac
  shift
done

if [[ $submit_flg = "1" ]]; then
  ./_submit.sh $task_id
  exit $?;
fi

alias c++oj 1>&2

source_file=${task_id}.cpp
input_file=${task_id}.in.txt
output_file=${task_id}.out.txt

if [[ $generate_flg = "1" ]]; then
  source_file=${task_id}_gen.cpp
  input_file=${task_id}.stress.in.txt
  output_file=${task_id}.stress.out.txt
  doit "$COMPILE_CMD ${source_file} && time ./a.out --create > ${input_file}"
  doit "$COMPILE_CMD ${source_file} && time ./a.out --solve < ${input_file} > ${output_file}"

  exit 0
fi

if [[ $stress_flg = "1" ]]; then
  input_file=${task_id}.stress.in.txt
  output_file=${task_id}.stress.out.txt
fi

if [[ $diff_flg = "0" ]]; then
  doit "$COMPILE_CMD ${source_file} && time ./a.out < ${input_file}"
else
  doit "$COMPILE_CMD ${source_file} && time ./a.out < ${input_file} | diff -b -B - ${output_file}"
fi

doit "python3 atcoder/expander.py ${source_file} -c > _combined.cpp 2>/dev/null"
