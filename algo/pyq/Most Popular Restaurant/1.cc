
/*
 * 一个map, 里面有好多点，。还有很多相同面积的方框，找到所有点超过一定数量的方框
 *
 * 方框是Restaurant, 点是人
 */



int popularRestaurants(const vector<Point> &points, const vector<Rectangles> &rects,
    int limit) {
  RTree rt(rects);
  forEach(Point p, points) {
    vector<Rectangle> located_rects = rt.find(p);
    forEach(Rectangle rect, located_rects) {
      rect.addOne();
    }
  }
  forEach(Rectangle rect, rects) {
    if (rect.count >= limit) {
      // Rectaurant we want
    }
  }
}
