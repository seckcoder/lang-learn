import com.google.common.hash.BloomFilter;
import com.google.common.hash.Funnels;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.filecache.DistributedCache;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.mapreduce.TableReducer;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.VIntWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

import java.io.FileInputStream;
import java.io.IOException;
import java.net.URI;
import java.nio.charset.StandardCharsets;
import java.util.*;

/**
 * Created by seckcoder on 14-11-22.
 */

class Global {
  public static int min_ngram_count = 0;
  public static int max_word_count = 0;
  public static void set(int min_ngram_count_, int max_word_count_) {
    min_ngram_count = min_ngram_count_;
    max_word_count = max_word_count_;
  }
};


class WordCountPair implements Comparable<WordCountPair>  {
  public String word;
  public int count;
  public WordCountPair(String str) {
    parse(str);
  }
  public int compareTo(WordCountPair other) {
    assert(word.equals(other.word));
    // sort reversely
    if (count > other.count) {
      return -1;
    } else if (count == other.count) {
      return 0;
    } else {
      return 1;
    }
  }
  public void parse(String str) {
    String[] sub_strs = str.split("\t");
    assert(sub_strs.length == 2);
    word = sub_strs[0].trim();
    count = Integer.parseInt(sub_strs[1]);
  }
};

public class GenProb {
  public static class Map extends Mapper<LongWritable, Text, Text, Text> {
    private Text text_key = new Text();
    private Text text_value = new Text();

    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException, NumberFormatException {
      String line = value.toString().trim();
      if (line.length() > 0) {
        String[] fields = line.split("\t");
        assert(fields.length == 2);
        int ngram_count = Integer.parseInt(fields[1]);
        // ngram count limit
        if (ngram_count >= Global.min_ngram_count) {
          String[] sub_strs = fields[0].split(" ");
          if (sub_strs.length > 1) {
            writePhasePlusWord(context, sub_strs, fields);
          }
        }
//        if (sub_strs.length == 1) {
//          writePhase(context, fields);
//        } else if (sub_strs.length > 1) {
//          writePhase(context, fields);
//          writePhasePlusWord(context, sub_strs, fields);
//        }
      }
    }
//    void writePhase(Context context, String[] fields) throws IOException, InterruptedException {
//      text_key.set(fields[0]);
//      text_value.set(fields[1]);
//      context.write(text_key, text_value);
//    }
    void writePhasePlusWord(Context context, String[] sub_strs, String[] fields) throws IOException, InterruptedException {
      StringBuilder key_builder = new StringBuilder();
      for (int i = 0; i < sub_strs.length - 1; i++) {
        key_builder.append(sub_strs[i]);
      }
      String str_value = sub_strs[sub_strs.length - 1] + "\t" + fields[1];
      text_key.set(key_builder.toString());
      text_value.set(str_value);
      context.write(text_key, text_value);
    }
  }

  public static class Reduce extends TableReducer<Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
            throws IOException, InterruptedException {
      ArrayList<WordCountPair> arr_lst = new ArrayList<WordCountPair>();
      for (Text val: values) {
        arr_lst.add(new WordCountPair(val.toString()));
      }
      Collections.sort(arr_lst);

      Put put = new Put(key.getBytes());
      for (int i = 0; i < arr_lst.size() && i <= Global.max_word_count; i++) {
        put.add(Bytes.toBytes("c1"), Bytes.toBytes(String.valueOf(i)), Bytes.toBytes(arr_lst.get(i).word));
      }
      context.write(key, put);
    }
  }

  public static void outputToHBase(String[] args) throws Exception {
    Configuration conf = HBaseConfiguration.create();

    conf.setInt("hbase.zookeeper.property.clientPort", 5181);
    Job job = new Job(conf, "ngram");

    job.setJarByClass(GenProb.class);
    job.setMapperClass(Map.class);
    job.setMapOutputKeyClass(Text.class);
    job.setMapOutputValueClass(Text.class);
    FileInputFormat.setInputPaths(job, new Path(args[0]));
    // set output table name
    TableMapReduceUtil.initTableReducerJob("cloud", Reduce.class, job);
    job.setReducerClass(Reduce.class);
    Global.set(Integer.parseInt(args[1]), Integer.parseInt(args[2]));

    job.waitForCompletion(true);
  }


  /**
   * Main
   * @param args: [input path, min ngram count, max word count]
   * @throws Exception
   */
  public static void main(String[] args) throws Exception {
    outputToHBase(args);
  }
}