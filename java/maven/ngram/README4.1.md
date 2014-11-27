Inverted Index with Stop Word removed(Bonus)
=====


Files:

 - src/main/GenBloomFilter.java : used to generate bloom filter from stop word dict
 - src/main/NGram.java : the mapreduce file used to invert index.
 - pom.xml : in case anyone wants to build it, this is the `maven` configuration file

Usage:

  first generate the bloom filter form stop world:

  - mvn compile
  - mvn exec:java -Dexec.mainClass="GenBloomFilter" -Dexec.args="english.stop filter.dat 500 check_stop"

  This will generate a bloom filter file:`filter.dat` used by mapreducer to filter stop word. Your need to specify the `numInsertions`(500 here) for BloomFilter when the size of stop word file changed

  then run mapreduce:

  - mvn package
  - hadoop jar target/ngram-1.0-SNAPSHOT.jar NGram `input-path` `output-path` `bloom-filter.dat`
