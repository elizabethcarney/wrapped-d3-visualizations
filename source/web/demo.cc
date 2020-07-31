//#include "../../third-party/Empirical/source/web/Document.h"
#include "../../third-party/Empirical/source/web/d3/d3_init.h"
#include "../../third-party/Empirical/source/web/d3/selection.h"
#include "../../third-party/Empirical/source/web/d3/scales.h"
#include "../../third-party/Empirical/source/web/d3/axis.h"

/* struct ExampleJSONData { EMP_BUILD_INTROSPECTIVE_TUPLE( int, x, int, y, std::string, name ) };
int get_x(ExampleJSONData d, int i, int j) { return d.x(); };
int get_y(ExampleJSONData d, int i, int j) { return d.y(); };
std::string get_name(ExampleJSONData d, int i, int j) { return d.name(); }; */

void MakeScatterplot_Foundation() {

  emp::vector<emp::vector<double>> example_data = {
    {1,0}, {5,1}, {8,0.5}, {14,2.5}, {15,1.6}, {19,2.3}, {28,2.5}, {28,3.4}, {33,3.2},
    {35,2.2}, {43,4.8}, {48,2.6}, {58,3.4}, {63,5.2}, {67,3.9}, {64,5.7}, {75,4},
    {34,3.3}, {40,4.1}, {52,3.3}, {52,4.7}, {55,4.5}, {67,4.9}, {66,6.5}, {75,5.6},
    {79,5.4}, {83,5.8}, {93,6.4}, {100,7}, {97,7}, {98,6.2}, {99,6.9}, {100,6.8}
  };

  //D3::Dataset dataset;
  //dataset.LoadDataFromFile(example_data.json);

  std::string x_label = "days in quarantine";
  std::string y_label = "days per week wearing sweatpants";

  double svg_width = 700;
  double svg_height = 500;
  double graph_width = 600;
  double graph_height = 400;

  double padding_left = 60;
  double padding_top = (svg_height - graph_height)/2;

  //double data_point_radius = 3;

  // set up div and responsive svg
  D3::Selection viz_div = D3::Select("#foundation-viz");
  D3::Selection viz_svg = viz_div.Append("svg").SetAttr("id", "scatterplot_svg")
                          .SetAttr("viewBox", "0 0 " +std::to_string(svg_width)+ " " +std::to_string(svg_height));

  // set up scales
  D3::LinearScale x_scale = D3::LinearScale();
  x_scale.SetDomain(0, 100).SetRange(padding_left, graph_width+padding_left);
  D3::LinearScale y_scale = D3::LinearScale();
  y_scale.SetDomain(0, 7).SetRange(graph_height+padding_top, padding_top);

  // set up axes with shifts according to scale range
  D3::Axis<D3::LinearScale> bottom_axis = D3::Axis<D3::LinearScale>(0, graph_height+padding_top, "bottom", x_label).SetScale(x_scale).Draw(viz_svg);
  D3::Axis<D3::LinearScale> left_axis = D3::Axis<D3::LinearScale>(padding_left, 0, "left", y_label).SetScale(y_scale).Draw(viz_svg);

  // set up circle data points
  D3::Selection data_points = viz_svg.SelectAll("circle");
  // bind data and assign a circle to each data point without a DOM element
  // (use lambdas for ApplyScale so that it's in scope)
  D3::Selection circles = viz_svg.SelectAll("circle")
          .Data(example_data)
          .EnterAppend("circle")
          .SetAttr("cx", [&example_data, &x_scale](int d, int i, int j) { return x_scale.ApplyScale<double, double>(example_data.at(i).at(0)); })
          .SetAttr("cy", [&example_data, &y_scale](int d, int i, int j) { return y_scale.ApplyScale<double, double>(example_data.at(i).at(1)); })
          .SetAttr("r", 3);

}

int main() {

  D3::InitializeEmpD3();

  MakeScatterplot_Foundation();

  return 0;

}