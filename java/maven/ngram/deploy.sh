#!/bin/bash


scp -i ~/15619Demo.pem.txt out/artifacts/ngram_jar/ngram.jar run.sh hadoop@$1:~/
