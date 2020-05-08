class MoveLinear {
  private:
    float x;
    float y;
    float z;

  public:
    MoveLinear(float, float, float);
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }
};

MoveLinear::MoveLinear(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
