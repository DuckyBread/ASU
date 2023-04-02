#include <fstream>
#include <iostream>
#include <string>

class TIntegrator {
 public:
  TIntegrator() = default;
  TIntegrator(float newScale, float newMin, float newMax)
      : scale_(newScale), MIN_(newMin), MAX_(newMax) {}
  ~TIntegrator() {}
  TIntegrator(const TIntegrator& i)
      : scale_(i.scale_), MIN_(i.MIN_), MAX_(i.MAX_), value_(i.value_) {}
  TIntegrator(TIntegrator&&) = delete;

  void SetValue(float value) { value_ = value; }
  void SetScale(float scale) { scale_ = scale; }
  void SetMin(float min) { MIN_ = min; }
  void SetMax(float max) { MAX_ = max; }

  float GetValue() { return value_; }
  float GetScale() { return scale_; }
  float GetMin() { return MIN_; }
  float GetMax() { return MAX_; }

  float Proc(float dt, float u) {
    value_ += scale_ * u * dt;
    (value_ > MAX_) ? (value_ = MAX_) : ((value_ < MIN_) ? (value_ = MIN_) : 1);
    return value_;
  }
  void Reset() { value_ = 0; }
  void Print() {
    std::cout << "Value:\t" << value_ << "\nScale:\t" << scale_ << "\nMin:\t"
              << MIN_ << "\nMax:\t" << MAX_ << std::endl;
  }

 private:
  float scale_ = 1;
  float MIN_ = 0;
  float MAX_ = 0;
  float value_ = 0;
};

class TDerivative {
 public:
  TDerivative() = default;
  TDerivative(float newScale, float newMin, float newMax)
      : scale_(newScale), MIN_(newMin), MAX_(newMax) {}
  ~TDerivative() {}
  TDerivative(const TDerivative& i)
      : scale_(i.scale_),
        MIN_(i.MIN_),
        MAX_(i.MAX_),
        value_(i.value_),
        prevU_(i.prevU_) {}
  TDerivative(TDerivative&&) = delete;

  void SetValue(float value) { value_ = value; }
  void SetScale(float scale) { scale_ = scale; }
  void SetMin(float min) { MIN_ = min; }
  void SetMax(float max) { MAX_ = max; }
  void SetPrevU(float prev) { prevU_ = prev; }

  float GetValue() { return value_; }
  float GetScale() { return scale_; }
  float GetMin() { return MIN_; }
  float GetMax() { return MAX_; }
  float GetPrevU() { return prevU_; }

  float Proc(float dt, float u) {
    value_ = scale_ * (u - prevU_) / dt;
    prevU_ = u;
    return value_;
  }

  void Reset() { value_ = prevU_ = 0; }
  void Print() {
    std::cout << "Value:\t" << value_ << "\nScale:\t" << scale_ << "\nMin:\t"
              << MIN_ << "\nMax:\t" << MAX_ << "\nPrev_u:\t" << prevU_
              << std::endl;
  }

 private:
  float scale_ = 1;
  float MIN_ = 0;
  float MAX_ = 0;
  float value_ = 0;
  float prevU_ = 0;
};

class TAperiodic {
 public:
  TAperiodic() = default;
  TAperiodic(float newScale, float newMin, float newMax, float newT)
      : scale_(newScale), MIN_(newMin), MAX_(newMax), T_(newT) {}
  ~TAperiodic() {}
  TAperiodic(const TAperiodic& i)
      : scale_(i.scale_),
        MIN_(i.MIN_),
        MAX_(i.MAX_),
        T_(i.T_),
        value_(i.value_) {}
  TAperiodic(TAperiodic&&) = delete;

  void SetValue(float value) { value_ = value; }
  void SetScale(float scale) { scale_ = scale; }
  void SetMin(float min) { MIN_ = min; }
  void SetMax(float max) { MAX_ = max; }
  void SetT(float T) { T_ = T; }

  float GetValue() { return value_; }
  float GetScale() { return scale_; }
  float GetMin() { return MIN_; }
  float GetMax() { return MAX_; }
  float GetT() { return T_; }

  float Proc(float dt, float u) {
    value_ += +dt * (scale_ * u - value_) / T_;
    return value_;
  }

  void Reset() { value_ = 0; }
  void Print() {
    std::cout << "Value:\t" << value_ << "\nScale:\t" << scale_ << "\nMin:\t"
              << MIN_ << "\nMax:\t" << MAX_ << "\nT:\t" << T_ << std::endl;
  }

 private:
  float scale_ = 1;
  float MIN_ = 0;
  float MAX_ = 0;
  float T_ = 0;
  float value_ = 0;
};

class TSecondStep {
 public:
  TSecondStep() = default;
  TSecondStep(float newScale, float newMin, float newMax, float newT,
              float newD)
      : scale_(newScale), MIN_(newMin), MAX_(newMax), T_(newT), D_(newD) {}
  ~TSecondStep() {}
  TSecondStep(const TSecondStep& i)
      : scale_(i.scale_),
        MIN_(i.MIN_),
        MAX_(i.MAX_),
        T_(i.T_),
        D_(i.D_),
        y_(i.y_),
        dy_(i.dy_) {}
  TSecondStep(TSecondStep&&) = delete;

  void SetY(float y) { y_ = y; }
  void SetDy(float dy) { dy_ = dy; }
  void SetD(float D) { D_ = D; }
  void SetScale(float scale) { scale_ = scale; }
  void SetMin(float min) { MIN_ = min; }
  void SetMax(float max) { MAX_ = max; }
  void SetT(float T) { T_ = T; }

  float GetY() { return y_; }
  float GetDy() { return dy_; }
  float GetD() { return D_; }
  float GetScale() { return scale_; }
  float GetMin() { return MIN_; }
  float GetMax() { return MAX_; }
  float GetT() { return T_; }

  float Proc(float dt, float u) {
    dy_ += dt * ((scale_ * u - 2 * D_ * T_ * dy_ - y_) / (T_ * T_));
    y_ += dt * dy_;
    return y_;
  }
  void Reset() { y_ = dy_ = 0; }
  void Print() {
    std::cout << "y:\t" << y_ << "\ndy:\t" << dy_ << "\nD:\t" << D_
              << "\nscale:\t" << scale_ << "\nMin:\t" << MIN_ << "\nMax:\t"
              << MAX_ << "\nT:\t" << T_ << std::endl;
  }

 private:
  float scale_;
  float MIN_;
  float MAX_;
  float T_;
  float D_;
  float y_;
  float dy_;
};

int main() {
  std::cout << "Start" << std::endl;

  float t0 = -1.;
  float tmax = 25.;
  float dt = 0.001;

  std::string file_name;
  std::cout << "Enter file name:\n";
  std::cin >> file_name;
  (file_name.size() != 0) ? (file_name += ".txt") : (file_name = "Out.txt");
  std::ofstream FS(file_name);

  TIntegrator I1(2, -1000, 1000);
  TDerivative I2(2, -1000, 1000);
  TAperiodic I3(2, -1000, 1000, 0.5);
  TSecondStep I4(2, -1000, 1000, 0.5, 0.2);

  /* This block can be skipped, because only variable scale_ = 1, other
   * variables eq to 0 */
  I1.Reset();
  I2.Reset();
  I3.Reset();
  I4.Reset();
  /* ************************************************************************************
   */

  for (float t = t0; t < tmax; t += dt) {
    float u = (t < 0) ? (0.) : (1.);

    I1.Proc(dt, u);
    I2.Proc(dt, u);
    I3.Proc(dt, u);
    I4.Proc(dt, u);

    FS << t << " " << u << " " << I1.GetValue() << " " << I2.GetValue() << " "
       << I3.GetValue() << " " << I4.GetY() << std::endl;
  }

  std::cout << "End" << std::endl;
  return 0;
}
