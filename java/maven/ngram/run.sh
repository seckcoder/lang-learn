#!/bin/bash

HADOOP_CLASSPATH=`${HBASE_HOME}/bin/hbase classpath` hadoop jar ngram-1.0-SNAPSHOT.jar GenNGram /mnt/input /mnt/output /mnt/cache/english.stop#english.stop
