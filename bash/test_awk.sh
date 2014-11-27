#!/usr/bin/env bash

cat test_data | awk '$1 ~ "liwei" {print $1}'
