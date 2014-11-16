#!/bin/bash


scp -i ~/15619Demo.pem.txt ./english.stop target/ngram-1.0-SNAPSHOT.jar run.sh hadoop@$1:~/
