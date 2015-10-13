package org.me;

/**
 * Created by seckcoder on 10/12/15.
 */

public class SearchRegion {
  public SearchPublicationDate dtLow;
  public SearchPublicationDate dtHigh;
  SearchRegion(SearchPublicationDate theDtLow, SearchPublicationDate theDtHigh)
  {
    dtLow = theDtLow;
    dtHigh = theDtHigh;
  }
  @Override
  public String toString()
  {
    return "LineString(" + Integer.toString(dtLow.year) + " " + Integer.toString(dtLow.month) + ","
      + Integer.toString(dtHigh.year) + " " + Integer.toString(dtHigh.month) + ")";
  }
}