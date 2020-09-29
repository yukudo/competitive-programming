#!/bin/bash

taskid="$1"

# The file '.last_contest_id.txt expires 5 hours.'
find .last_contest_id.txt -mmin +300 -a -type f -exec rm -f {} \;
contestid=$(touch .last_contest_id.txt && cat .last_contest_id.txt)
if [[ -z $contestid ]]; then
  echo "Invalid contestid. You should run the 'makeio' command to ready the file '.last_contest_id.txt'."
  exit 1
fi

echo -n "Are you sure you wnat to submit '$taskid' to '$contestid'? [y/N]: "
read confirm
if [[ "$confirm" == "y" ]] || [[ "$confirm" == "Y" ]] ; then
  python3 atcoder_tool/atcoder.py submit $taskid $contestid
else
  echo ""
fi

