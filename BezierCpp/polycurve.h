#ifndef POLYCURVE_H
#define POLYCURVE_H

#include "bezier.h"
#include <deque>

namespace Bezier
{
class PolyCurve;

typedef std::shared_ptr<PolyCurve> PolyCurvePtr;
typedef std::shared_ptr<const PolyCurve> ConstPolyCurvePtr;

class PolyCurve
{
private:

  std::deque<CurvePtr> curves_;
  // TODO: Continuity isn't implemented yet

  PolyCurve(const std::deque<CurvePtr>& curve_list);

public:
  PolyCurve(CurvePtr& curve1);
  PolyCurve(std::vector<CurvePtr>& curve_list);

  void insertAt(uint idx, CurvePtr& curve);
  void insertFront(CurvePtr& curve);
  void insertBack(CurvePtr& curve);
  void removeAt(uint idx);
  void removeFirst();
  void removeBack();
  PolyCurve getSubPolyCurve(uint idx_l, uint idx_r);
  uint getSize() const;
  uint getCurveIdx(const CurvePtr& curve) const;
  CurvePtr getCurvePtr(uint idx) const;

  PointVector getPolyline(double smoothness = 1.0001, double precision = 1.0) const;
  std::pair<Point, Point> getEndPoints() const;

  Point valueAt(double t) const;
  double curvatureAt(double t) const;
  Vec2 tangentAt(double t, bool normalize = true) const;
  Vec2 normalAt(double t, bool normalize = true) const;

  BBox getBBox(bool use_roots = true) const;

  std::vector<Point> getPointsOfIntersection(const Curve& curve, bool stop_at_first = false,
                                             double epsilon = 0.001) const;
  std::vector<Point> getPointsOfIntersection(const PolyCurve& poly_curve, bool stop_at_first = false,
                                             double epsilon = 0.001) const;
  double projectPoint(const Point& point, double step = 0.01) const;
};
}
#endif // POLYCURVE_H