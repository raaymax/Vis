#!/bin/bash

python merge.py imdump.xml $1 > $2
xmllint --c14n11 --format $2
