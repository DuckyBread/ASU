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
      : value_(i.value_), scale_(i.scale_), MIN_(i.MIN_), MAX_(i.MAX_) {}
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
    SetValue(GetValue() + GetScale() * u * dt);
    (GetValue() > GetMax()) ? (SetValue(GetMax())) : ((GetValue() < GetMin()) ? (SetValue(GetMin())) : 1);
    return GetValue();
  }

  std::ofstream ClassIntegrator(float dt, float u) {
    std::string file_name;
    std::cout << "Enter file name:\n";
    std::cin >> file_name;
    file_name += ".txt";

    std::ofstream FS(file_name);

    for (auto t = time_start; t <= time_end; t += dt) {
      float u = (t < 0) ? (0.) : (1.);
      SetValue(GetValue() + GetScale() * u);
      FS << t << "\t" << u << "\t" << GetValue() << std::endl;
    }

    return FS;
  }

  void ResetIntegrator(): value_(0) {}
  void PrintIntegrator() {
    std::cout << "Value:\t" << GetValue() << "\nScale:\t" << GetScale() << "\nMin:\t"
              << GetMin() << "\nMax:\t" << GetMax() << std::endl;
  }

 private:
  float value_ = MIN_ = MAX_ = 0,scale_ = 1;
};

class TDerivative {
 public:
  TDerivative() = default;
  TDerivative(float newScale, float newMin, float newMax)
      : scale_(newScale), MIN_(newMin), MAX_(newMax) {}
  ~TDerivative() {}
  TDerivative(const TIntegrator& i)
      : value_(i.value_), scale_(i.scale_), MIN_(i.MIN_), MAX_(i.MAX_), prevU_(i.prevU_) {}
  TDerivative(TIntegrator&&) = delete;

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
    SetValue(GetScale() * (u - GetPrevU())  / dt);
    SetPrevU(u);
    return GetValue();
  }

  void ResetTDerivative(): value_(0), prevU_(0) {}
  void PrintTDerivative() {
    std::cout << "Value:\t" << GetValue() << "\nScale:\t" << GetScale() << "\nMin:\t"
              << GetMin() << "\nMax:\t" << GetMax() << "\nPrev_u:\t" << GetPrevU() << std::endl;
  }

 private:
  float value_ = MIN_ = MAX_ = 0, scale_ = 1, prevU_ = 0;
};

std::ofstream integrator(float time_start, float time_end, float dt,
                         float gain);

int main() {
  float t0 = -1.;   /* Start time */
  float tmax = 10.; /* Finish time */
  float dt = 0.001; /* Step = 0.01 s */
  // float gain = 1.5;
  Integrator aboba(0, 1.5f, 0, 0);

  std::cout << "Start\n";
  // std::ofstream FS = integrator(t0, tmax, dt, gain);
  std::ofstream FS = aboba.ClassIntegrator(t0, tmax, dt);
  aboba.PrintIntegrator();
  std::cout << "end of the prog\n";

  return 0;
}

std::ofstream integrator(float time_start, float time_end, float dt,
                         float gain) {
  std::string file_name;
  std::cout << "Enter file name:\n";
  std::cin >> file_name;
  file_name += ".txt";

  std::ofstream FS(file_name);
  float intgr = 0.;

  for (float t = time_start; t <= time_end; t += dt) {
    float u = (t < 0) ? (0.) : (1.);
    intgr += gain * u;
    FS << t << "\t" << u << "\t" << intgr << std::endl;
  }
  return FS;
}
