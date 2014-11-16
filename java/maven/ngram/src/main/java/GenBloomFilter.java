/**
 * Created by seckcoder on 14-11-15.
 */

import java.io.IOException;
import com.google.common.hash.BloomFilter;
import com.google.common.hash.Funnels;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;

public class GenBloomFilter {

  private static void checkBloomFilter(BloomFilter<CharSequence> filter, String fpath) throws IOException {
    BufferedReader reader = new BufferedReader(
            new InputStreamReader(
                    new FileInputStream(fpath), "UTF-8"
            )
    );
    String line;
    while ((line = reader.readLine()) != null) {
      line = line.trim();
      System.out.println(filter.mightContain(line));
    }
  }

  /**
   * Just to check whether we can read from the dumped bloom filter...
   * @param dpath
   * @param checkpath
   * @throws IOException
   */
  private static void checkReadFromBloomFilter(String dpath, String checkpath) throws IOException {
    BloomFilter<CharSequence> bloomFilter = BloomFilter.readFrom(new FileInputStream(dpath),
            Funnels.stringFunnel(StandardCharsets.UTF_8));
    System.out.println("----------");
    checkBloomFilter(bloomFilter, checkpath);
  }

  /**
   *
   * @param args: args[0] is the stop word file name, args[1] is filter output file name,args[2] is the expected number of insertions. args[3] is the file used to check bloomfilter
   * @throws IOException
   */
  public static void main(String[] args) throws IOException {
    BloomFilter<CharSequence> bloomFilter = BloomFilter.create(Funnels.stringFunnel(StandardCharsets.UTF_8), Integer.parseInt(args[2]));
    BufferedReader reader = new BufferedReader(
            new InputStreamReader(
                    new FileInputStream(args[0]), "UTF-8")
    );
    String line;
    while ((line = reader.readLine()) != null) {
      line = line.trim();
      bloomFilter.put(line);
    }
    checkBloomFilter(bloomFilter, args[3]);
    FileOutputStream fs = new FileOutputStream(args[1]);
    bloomFilter.writeTo(fs);
    fs.close();
    reader.close();
    //checkReadFromBloomFilter(args[1], args[3]);
  }
}
