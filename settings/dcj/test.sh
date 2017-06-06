#!/bin/bash
# 
#  usage 
#      ./test.sh [your_source.cpp] [nodes]
#

cd $(dirname $0)

function usage(){
    echo "  usage:"
    echo "    ./test.sh [your_source.cpp] [nodes]"
}

your_source=$1
nodes=$2

# validate input parameters
if [[ $# != 2 ]] ; then
  usage
  exit 1
fi
if [[ "${your_source}" != *.cpp ]] ; then
  usage
  exit 1
fi
if [[ ! "${nodes}" -ge 1 ]] ; then 
  usage
  exit 1
fi

f=$(ls *.h | head -1)
problem_name=${f%%.*}
echo problem_name=${problem_name}

BUILD_DIR="./build"
mkdir ${BUILD_DIR}
cp ${your_source} ${BUILD_DIR}
for h in $(ls *.h) ; do
  echo '--------------------'
  echo ${h}
  cp ${h} ${BUILD_DIR}/${problem_name}.h
  echo "> /root/dcj_tool/dcj.sh test --source ${BUILD_DIR}/${your_source} --nodes ${nodes}"
  /root/dcj_tool/dcj.sh test --source ${BUILD_DIR}/${your_source} --nodes ${nodes}
  rm ${BUILD_DIR}/${problem_name}.h
done
echo '--------------------'
rm -rf ${BUILD_DIR}

exit 0
