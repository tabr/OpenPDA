// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <serstream>
#include <Arduino.h>

void more(void)
{
  Serial.print("more");

  std::cout << 1.0f;
}
