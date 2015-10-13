package org.me;

/**
 * Created by seckcoder on 10/12/15.
 */
public class SearchPublicationDate {
  public int year;
  public int month;
  public SearchPublicationDate(int theYear)
  {
    year = theYear;
    month = 1; // month always equal to 1
  }
  @Override
  public String toString()
  {
    return "Point(" + Integer.toString(year) + " " + Integer.toString(month) + ")";
  }
}
