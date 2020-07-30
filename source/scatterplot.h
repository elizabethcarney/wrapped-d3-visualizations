/*
 * SCATTERPLOT.H
 *
 * A pre-built Empirical D3-wrapper visualization that constructs a scatterplot.
 *
 * @file scatterplot.h
 * @author Elizabeth Carney
 * @date 2020
 */

#include "../third-party/Empirical/source/web/d3/d3_init.h"
#include "../third-party/Empirical/source/web/d3/selection.h"
#include "../third-party/Empirical/source/web/d3/scales.h"
#include "../third-party/Empirical/source/web/d3/axis.h"

#ifndef EMP_D3_SCATTERPLOT_H
#define EMP_D3_SCATTERPLOT_H

namespace D3 {

  template <typename DATA_TYPE = emp::array<double, 2>,
            typename X_SCALE_TYPE = D3::LinearScale,
            typename Y_SCALE_TYPE = D3::LinearScale >
  class Scatterplot : public D3_Base {

    private:

      // Parameters
      std::string x_label;
      std::string y_label;
      double width;
      double height;

      // Default formatting values
      double axis_width = 60;
      double y_margin = 10;
      double x_margin = 30;

      // Default scale domains
      double x_min = 0;
      double x_max = 1000;
      double y_min = 0;
      double y_max = 1000;

      // Components of the graph
      X_SCALE_TYPE x_scale;
      Y_SCALE_TYPE y_scale;
      D3::Axis<X_SCALE_TYPE> x_axis;
      D3::Axis<Y_SCALE_TYPE> y_axis;

    public:
      // Constructor
      Scatterplot(std::string x_label = "", std::string y_label = "", int width = 800, int height = 400) {

        this->x_label = x_label;
        this->y_label = y_label;
        this->width = width;
        this->height = height;

        D3::Selection * svg = GetSVG();

        // Set up scales
        x_scale = X_SCALE_TYPE();
        y_scale = Y_SCALE_TYPE();
        x_scale.SetDomain(emp::array<double, 2>{{x_min, x_max}})
               .SetRange(emp::array<double, 2>{{axis_width, GetWidth() - x_margin}});
        y_scale.SetDomain(emp::array<double, 2>{{y_max, y_min}})
               .SetRange(emp::array<double, 2>{{y_margin, (double)GetHeight() - axis_width}});

        // Draw axes
        x_axis = D3::Axis<X_SCALE_TYPE>("bottom", variables[0]);
        x_axis.SetScale(x_scale);
        y_axis = D3::Axis<Y_SCALE_TYPE>("left", variables[1]);
        y_axis.SetScale(y_scale);
        D3::DrawAxes(x_axis, y_axis, *svg);

      }

      ~Scatterplot() {
        delete x_scale;
        delete y_scale;
        delete x_axis;
        delete y_axis;
      }

  };

}

#endif