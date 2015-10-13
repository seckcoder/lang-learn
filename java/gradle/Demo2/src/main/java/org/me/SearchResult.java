package org.me;

import org.apache.lucene.document.Document;

/**
 * Created by seckcoder on 10/12/15.
 */


public class SearchResult {
  public int id; // publication id
  public String content; // author or title
  public enum ResultType {
    TITLE, AUTHOR
  }
  public ResultType type;
  SearchResult()
  {

  }
  SearchResult(Document fetcher)
  {
    id = Integer.parseInt(fetcher.get("id"));
    String title = fetcher.get("title");
    if (title != null)
    {
      content = title;
      type = ResultType.TITLE;
    } else {
      String author = fetcher.get("author");
      content = author;
      type = ResultType.AUTHOR;
    }
  }
}