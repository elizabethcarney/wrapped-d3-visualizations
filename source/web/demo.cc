#include "../../third-party/Empirical/source/web/Document.h"
#include "../../third-party/Empirical/source/web/d3/d3_init.h"
#include "../../third-party/Empirical/source/web/d3/selection.h"
#include "../../third-party/Empirical/source/web/d3/scales.h"
#include "../../third-party/Empirical/source/web/d3/axis.h"

/* struct ExampleJSONData { EMP_BUILD_INTROSPECTIVE_TUPLE( int, x, int, y, std::string, name ) };
int get_x(ExampleJSONData d, int i, int j) { return d.x(); };
int get_y(ExampleJSONData d, int i, int j) { return d.y(); };
std::string get_name(ExampleJSONData d, int i, int j) { return d.name(); }; */

std::function<int(int, int, int)> return_data = [](int d, int i, int j){ return d; };

void MakeScatterplot() {

  //emp::vector<emp::vector<int>> example_data = {{10,100}, {15,150}, {20,250}, {40,275}, {50,280}, {50,300}, {90,400}};
  emp::vector<int> example_data = {10, 15, 20, 40, 50, 60, 90};

  //D3::Dataset dataset;
  //dataset.LoadDataFromFile(example_data.json);

  std::string x_label = "Age";
  std::string y_label = "Total Ice Cream Cones Eaten";

  double svg_width = 700;
  double svg_height = 500;
  double graph_width = 600;
  double graph_height = 400;

  double padding_top = (svg_height - graph_height)/2;
  double padding_left = 60;

  double data_point_radius = 5;

  // set up div and svg
  D3::Selection viz_div = D3::Select("body").Append("div").SetAttr("id", "scatterplot_div");
  D3::Selection viz_svg = D3::Select("#scatterplot_div").Append("svg").SetAttr("id", "scatterplot_svg")
                          .SetAttr("width", svg_width).SetAttr("height", svg_height);

  // set up scales
  D3::LinearScale x_scale = D3::LinearScale();
  x_scale.SetDomain(0, 100).SetRange(padding_left, graph_width+padding_left);
  D3::LinearScale y_scale = D3::LinearScale();
  y_scale.SetDomain(0, 100).SetRange(graph_height+padding_top, padding_top);

  // set up axes with shifts according to scale range
  D3::Axis<D3::LinearScale> bottom_axis = D3::Axis<D3::LinearScale>(0, graph_height+padding_top, "bottom", x_label).SetScale(x_scale).Draw(viz_svg);
  D3::Axis<D3::LinearScale> left_axis = D3::Axis<D3::LinearScale>(padding_left, 0, "left", y_label).SetScale(y_scale).Draw(viz_svg);

  // set up circle data points
  D3::Selection data_points = viz_svg.SelectAll("circle");
  // bind data and assign a circle to each data point without a DOM element
  // (use lambdas for ApplyScale so that it's in scope)
  D3::Selection circles = viz_svg.SelectAll("circle")
          .Data(example_data, return_data)
          .EnterAppend("circle")
          .SetAttr("cx", [&x_scale](int d, int i, int j) { return x_scale.ApplyScale<int, int>(d); })
          .SetAttr("cy", [&y_scale](int d, int i, int j) { return y_scale.ApplyScale<int, int>(d); })
          .SetAttr("r", data_point_radius);

}

int main() {

  D3::InitializeEmpD3();

  MakeScatterplot();

  return 0;

}