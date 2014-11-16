
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.Reader;
import java.util.*;
import java.net.URI;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.filecache.DistributedCache;

public class NGram {

  public static class Map extends Mapper<LongWritable, Text, Text, Text> {
    private Text word = new Text();
    private HashSet<String> stopword_set = new HashSet<String>();
    @Override
    protected void setup(Context context) throws IOException {
      //URI[] cacheFiles = DistributedCache.getCacheFiles(context.getConfiguration());
      Path[] cacheFiles = DistributedCache.getLocalCacheFiles(context.getConfiguration());
      //loadStopWord("hdfs://english_stop");
      // Don't know why only this works
      loadStopWord(cacheFiles[0].toString());
    }

    private void loadStopWord(String uri) throws IOException {
      BufferedReader reader = new BufferedReader(
              new FileReader(uri));
      String line;
      while ((line = reader.readLine()) != null) {
        line = line.trim();
        stopword_set.add(line);
      }
      reader.close();
    }

    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
      String line = value.toString();
      FileSplit fs = (FileSplit) context.getInputSplit();
      Text location = new Text(fs.getPath().getName());
      StringTokenizer tokenizer = new StringTokenizer(line);
      while (tokenizer.hasMoreTokens()) {
        String token = tokenizer.nextToken().toLowerCase();
        if (!stopword_set.contains(token)) {
          word.set(token.replaceAll("\\W+", " "));
          context.write(word, location);
        }
      }
    }
  }

  public static class Reduce extends Reducer<Text, Text, Text, Text> {

    public void reduce(Text key, Iterable<Text> values, Context context)
            throws IOException, InterruptedException {
      //String books = new String("");
      HashSet<String> value_set = new HashSet<String>();
      for (Text loc : values) {
        value_set.add(loc.toString());
      }
      String books = new String(key.toString());
      books += ":";
      for (String loc : value_set) {
        books += loc;
        books += " ";
      }
      context.write(new Text(books), new Text(""));
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();

    Job job = new Job(conf, "ngram");
    job.setJarByClass(NGram.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);

    job.setMapperClass(Map.class);
    job.setReducerClass(Reduce.class);

    job.setInputFormatClass(TextInputFormat.class);
    job.setOutputFormatClass(TextOutputFormat.class);
    //job.setNumReduceTasks(4);

    URI uri = new URI(args[2]);
    DistributedCache.addCacheFile(uri, job.getConfiguration());

    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    job.waitForCompletion(true);
  }
}