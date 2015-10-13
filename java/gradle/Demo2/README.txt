
# Design Choices
Build index on title and author with Lucene.

The reason is we need to search for text(title or author) by keyword

Build geospatial index on year with Mysql.

The reason is for spatialSearch, we need not only search by text, but also search
by year. So we create a (year, month) pair as a coordinate. As there is no month data,
month always equal to 1.

# Demos

run command: `gradle run`.

There are three demos:
  - basic search for title
  - basic search for author
  - patial search for title

See screen-shot.png
