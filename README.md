# Реализация интегратора 1/р

## Общая информация
Для реализации простейшего интегратора на языке С++ в данной работе реализовано два подхода: с использованием классов и без его использования. На основе предсталенного кода в дальнейшем могут быть разработаны более сложные интеграторы.

## Информация о классе **Integrator**
Класс *Integrator* представлен из приватных полей (***value_, scale_, MIN_, MAX_***) и публичных методов (**сетеров, гетеров, вывод, сброс**). 
```c
class Integrator {
 public:
  Integrator();
  Integrator(float newValue, float newScale, float newMin, float newMax);
  Integrator(const Integrator&);
  Integrator(Integrator&&);
  ~Integrator();

  void SetValue(float value);
  void SetScale(float scale);
  void SetMin(float min);
  void SetMax(float max);

  float GetValue();
  float GetScale();
  float GetMin();
  float GetMax();

  void ResetIntegrator();
  void PrintIntegrator();

 private:
  float value_, scale_, MIN_, MAX_;
};
```
## Работа с Makefile
*Makefile* — набор инструкций для быстрой работы с проектом.

Makefile содержит такие инструкции, как:
1) ***all*** — выполняет инструкцию ***LR_2***
2) ***LR_2*** — производит компиляцию исполняемого файла LR_2
3) ***clean*** — удаляет полученные файлы и исполняемый файл 

Чтобы скомпилировать код, откройте файл с расширением `.cc` в ***DevCC++*** и нажмите на компиляцию.
