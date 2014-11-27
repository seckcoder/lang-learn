import com.google.common.hash.BloomFilter;
import com.google.common.hash.Funnels;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.filecache.DistributedCache;
import org.apache.hadoop.fs.Path;
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
import java.util.HashSet;
import java.util.Locale;
import java.util.StringTokenizer;

/**
 * Created by seckcoder on 14-11-22.
 */
public class GenNGram {
  public static class Map extends Mapper<LongWritable, Text, Text, IntWritable> {
    private Text word = new Text();
    private final static IntWritable one = new IntWritable(1);

    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
      String line = value.toString();
      line = line.replaceAll("[^a-zA-Z]+", " ").trim();
      if (line.length() > 0) {
        String[] subs = line.toLowerCase(Locale.ENGLISH).split("\\s+");
        writeNGrams(context, subs);
      }
    }
    public void writeNGrams(Context context, String[] subs) throws IOException, InterruptedException {
      if (subs.length == 0) return;
      StringBuilder[] builders = new StringBuilder[subs.length];
      for (int i = 0; i < subs.length; i++) {
        builders[i] = new StringBuilder(subs[i]);
      }
      int arr_len = subs.length;
      int ngram = 1; // number of grams in builder array.
      while (arr_len > 0 && ngram <= 5) {
        // we should print at most 5-grams.
        for (int i = 0; i < arr_len; i++) {
          word.set(builders[i].toString());
          context.write(word, one);
        }
        for (int i = 0; i < arr_len - 1; i++) {
          builders[i].append(" ");
          builders[i].append(subs[i+ngram].toString());
        }
        ngram += 1;
        arr_len -= 1;
      }
    }
  }

  public static class Reduce extends Reducer<Text, IntWritable, Text, IntWritable> {

    public void reduce(Text key, Iterable<IntWritable> values, Context context)
            throws IOException, InterruptedException {
      int sum_v = 0;
      for (IntWritable val : values) {
        sum_v += val.get();
      }
      context.write(key, new IntWritable(sum_v));
    }
  }

  /**
   * Main
   * @param args: [input path, output path]
   * @throws Exception
   */
  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    //conf.set("mapreduce.textoutputformat.separator", "\t");

    Job job = new Job(conf, "ngram");
    job.setJarByClass(GenNGram.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    job.setMapperClass(Map.class);
    job.setCombinerClass(Reduce.class);
    job.setReducerClass(Reduce.class);

    job.setInputFormatClass(TextInputFormat.class);
    job.setOutputFormatClass(TextOutputFormat.class);
    //job.setNumReduceTasks(4);

    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    job.waitForCompletion(true);
  }
}