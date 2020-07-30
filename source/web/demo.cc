#include "../../third-party/Empirical/source/web/Document.h"
#include "../../third-party/Empirical/source/web/d3/d3_init.h"
#include "../../third-party/Empirical/source/web/d3/selection.h"
#include "../../third-party/Empirical/source/web/d3/scales.h"
#include "../../third-party/Empirical/source/web/d3/axis.h"

void MakeScatterplot() {

  std::string x_label = "X Axis";
  std::string y_label = "Y Axis";

  std::string margin = "70";
  double svg_width = 500;
  double svg_height = 500;

  D3::Selection viz_div = D3::Select("body").Append("div").SetAttr("id", "scatterplot_div");
  D3::Selection viz_svg = D3::Select("#scatterplot_div").Append("svg").SetAttr("id", "scatterplot_svg")
                          .SetAttr("width", svg_width).SetAttr("height", svg_height);

  D3::LinearScale x_scale = D3::LinearScale();
  x_scale.SetDomain(0, 100).SetRange(50, 350);
  D3::LinearScale y_scale = D3::LinearScale();
  y_scale.SetDomain(0, 100).SetRange(50, 350);

  D3::Axis<D3::LinearScale> bottom_axis = D3::Axis<D3::LinearScale>("bottom", x_label).SetScale(x_scale);
  D3::Axis<D3::LinearScale> left_axis = D3::Axis<D3::LinearScale>("left", y_label).SetScale(y_scale);
  D3::DrawAxes(bottom_axis, left_axis, viz_svg);

}

int main() {

  D3::InitializeEmpD3();

  MakeScatterplot();

  return 0;

}