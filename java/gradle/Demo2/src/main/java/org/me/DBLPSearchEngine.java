package org.me;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.core.KeywordAnalyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.IntField;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.MultiFieldQueryParser;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.TopScoreDocCollector;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.RAMDirectory;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;

/**
 * Created by seckcoder on 10/12/15.
 */
public class DBLPSearchEngine {
  private static final String INDEX_DIRECTORY = "./index";
  private Directory directory;
  private Analyzer analyzer;
  Connection conn;
  DBLPSearchEngine()
  {
    try {
      Class.forName("com.mysql.jdbc.Driver").newInstance();
      conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dblp", "root", "");
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  public void createIndex()
  {
    try {
      Statement stmt = conn.createStatement();
      String sqlArticle = "select id, title from Article";
      String sqlAuthoring = "select articleId, author from Authoring";
      ResultSet articles = stmt.executeQuery(sqlArticle);

      // Directory directory = FSDirectory.open(Paths.get(INDEX_DIRECTORY));
      directory = new RAMDirectory();
      analyzer = new StandardAnalyzer();

      IndexWriterConfig writerConfig = new IndexWriterConfig(analyzer);
      // writerConfig.setOpenMode(IndexWriterConfig.OpenMode.CREATE);
      IndexWriter writer = new IndexWriter(directory, writerConfig);

      while (articles.next()) {
        Document doc = new Document();
        Field field = new IntField("id", articles.getInt("id"), Field.Store.YES);
        doc.add(field);

        field = new TextField("title", articles.getString("title"), Field.Store.YES);
        doc.add(field);

        writer.addDocument(doc);
      }

      ResultSet authorings = stmt.executeQuery(sqlAuthoring);

      while (authorings.next()) {
        Document doc = new Document();
        Field field = new IntField("id", authorings.getInt("articleId"), Field.Store.YES);
        doc.add(field);

        field = new TextField("author", authorings.getString("author"), Field.Store.YES);
        doc.add(field);

        writer.addDocument(doc);
      }
      writer.close();

    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  public SearchResult[] basicSearch(String query, int numResultsToSkip, int numResultsToReturn) throws ParseException, IOException
  {
    IndexReader reader = DirectoryReader.open(directory);
    IndexSearcher searcher = new IndexSearcher(reader);
    String[] fieldsToSearch = {"author", "title"};
    MultiFieldQueryParser parser = new MultiFieldQueryParser(fieldsToSearch, analyzer);

    Query parsedQuery = parser.parse(query);

    TopDocs hits = searcher.search(parsedQuery, numResultsToSkip + numResultsToReturn);

    ArrayList<SearchResult> res = new ArrayList<SearchResult>();
    for (int i = numResultsToSkip; i < Math.min(numResultsToSkip + numResultsToReturn, hits.scoreDocs.length); i++)
    {
      Document doc = searcher.doc(hits.scoreDocs[i].doc);
      res.add(new SearchResult(doc));
      // System.out.println("===== id: " + doc.get("id") + " title: " + doc.get("title") + " author: " + doc.get("author"));
    }
    SearchResult[] ret = new SearchResult[res.size()];
    res.toArray(ret);
    return ret;
  }

  public SearchResult[] spatialSearch(String query, SearchRegion region, int numResultsToSkip, int numResultsToReturn) throws ParseException, IOException, SQLException
  {
    IndexReader reader = DirectoryReader.open(directory);
    IndexSearcher searcher = new IndexSearcher(reader);
    String[] fieldsToSearch = {"title"};
    MultiFieldQueryParser parser = new MultiFieldQueryParser(fieldsToSearch, analyzer);
    Query parsedQuery = parser.parse(query);
    TopDocs hits = searcher.search(parsedQuery, numResultsToSkip + numResultsToReturn);
    Statement stmt = conn.createStatement();

    ArrayList<SearchResult> resArr = new ArrayList<SearchResult>();
    for (int i = numResultsToSkip; i < Math.min(numResultsToSkip + numResultsToReturn, hits.scoreDocs.length); i++)
    {
      Document doc = searcher.doc(hits.scoreDocs[i].doc);
      String articleId = doc.get("id");
      String sql = "select id, title, astext(dt) from article where MBRContains(GeomFromText('" + region.toString() + "'), dt) and id=" + articleId;
      ResultSet articles = stmt.executeQuery(sql);
      while (articles.next())
      {
        SearchResult res = new SearchResult();
        res.id = articles.getInt("id");
        res.content = articles.getString("title");
        res.type = SearchResult.ResultType.TITLE;
        resArr.add(res);
      }
    }
    SearchResult ret[] = new SearchResult[resArr.size()];
    resArr.toArray(ret);
    return ret;
  }
}
