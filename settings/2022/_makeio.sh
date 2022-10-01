#!/bin/bash

contestid="$1"
echo -n $contestid > .last_contest_id.txt
python3 atcoder_tool/atcoder.py makeio $contestid
