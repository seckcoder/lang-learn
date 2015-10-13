package org.me;

import java.io.File;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import org.apache.lucene.analysis.*;
import org.apache.lucene.analysis.core.KeywordAnalyzer;
import org.apache.lucene.document.*;
import org.apache.lucene.index.*;
import org.apache.lucene.queryparser.*;
import org.apache.lucene.search.*;
import org.apache.lucene.store.*;
import org.apache.lucene.util.Version;




/**
 * Created by seckcoder on 10/12/15.
 */
public class Demo {

  public static void main(String[] args) {

    DBLPSearchEngine engine = new DBLPSearchEngine();
    engine.createIndex();
    try {
      System.out.println("========= Demo basicSearch ============");
      System.out.println("==== Search for `calculus thoery`: ====");
      SearchResult[] resArr = engine.basicSearch("calculus theory", 0, 10);
      for (SearchResult res: resArr) {
        System.out.println(res.content);
      }
      System.out.println("==== Search for `Cheng Huang`: =====");
      resArr = engine.basicSearch("Cheng Huang", 0, 10);
      for (SearchResult res: resArr)
      {
        System.out.println(res.content);
      }
      System.out.println("========= Demo spatialSearch ============");
      System.out.println("==== Search for `calculus thoery` published between [1991, 2010]: ====");
      SearchRegion region = new SearchRegion(new SearchPublicationDate(1991), new SearchPublicationDate(2010));
      resArr = engine.spatialSearch("calculus theory", region, 0, 10);
      for (SearchResult res: resArr)
      {
        System.out.println(res.content);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}