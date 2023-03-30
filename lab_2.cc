#include <fstream>
#include <iostream>
#include <string>

class Integrator {
 public:
  Integrator() = default;
  Integrator(float newValue, float newScale, float newMin, float newMax)
      : value_(newValue), scale_(newScale), MIN_(newMin), MAX_(newMax) {}
  ~Integrator() {}
  Integrator(const Integrator& i)
      : value_(i.value_), scale_(i.scale_), MIN_(i.MIN_), MAX_(i.MAX_) {}
  Integrator(Integrator&&) = delete;

  void SetValue(float value) { value_ = value; }
  void SetScale(float scale) { scale_ = scale; }
  void SetMin(float min) { MIN_ = min; }
  void SetMax(float max) { MAX_ = max; }

  float GetValue() { return value_; }
  float GetScale() { return scale_; }
  float GetMin() { return MIN_; }
  float GetMax() { return MAX_; }

  std::ofstream ClassIntegrator(float time_start, float time_end, float dt) {
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

  void ResetIntegrator() {
    value_ = MIN_ = MAX_ = 0;
    scale_ = 1;
  }
  void PrintIntegrator() {
    std::cout << "Value:\t" << value_ << "\nScale:\t" << scale_ << "\nMin:\t"
              << MIN_ << "\nMax:\t" << MAX_ << std::endl;
  }

 private:
  float value_ = 0, scale_ = 1, MIN_ = 0, MAX_ = 0;
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
