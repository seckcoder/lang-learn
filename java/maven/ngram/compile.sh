#!/bin/bash


mkdir -p NGram_classes
javac -classpath ${HADOOP_HOME}/hadoop-core.jar -d NGram_classes NGram.java
