//  This file is part of Wrapped D3 Visualizations
//  Copyright (C) Elizabeth Carney, 2020.
//  Released under MIT license; see LICENSE

#include <iostream>

#include "web/web.h"

#include "../example.h"

namespace UI = emp::web;

UI::Document doc("emp_base");

int main()
{
  doc << "<h1>Hello, browser!</h1>";
  std::cout << "Hello, console!" << std::endl;
  return example();
}
