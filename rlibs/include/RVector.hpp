class RVector
{
  private:
    double fx, fy, fz;
  public:
    RVector (double x, double y, double z) { fx=x; fy=y; fz=z;};
    double getX() const {return fx};
    double getY() const {return fy};
    double getZ() const {return fz};
    void getXYZ (double & X, double & Y, double & Z) const
      {X=fx;Y=fy;Z=fy};
    void setX(double x) {fx=x;};
    void setY(double y) {fy=y;};
    void setZ(double z) {fz=z;};
};

