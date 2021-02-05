// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// sciplot includes
#include <sciplot/specs/FillSpecsOf.hpp>
#include <sciplot/specs/LineSpecsOf.hpp>
#include <sciplot/specs/PointSpecsOf.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class where options for the plotted element can be specified.
class PlotSpecs : public LineSpecsOf<PlotSpecs>, public PointSpecsOf<PlotSpecs>, public FillSpecsOf<PlotSpecs>
{
  public:
    /// Construct a PlotSpecs instance.
    /// @param what The string representing `what` to be plot (e.g., "'filename'", "sin(x)")
    /// @param use The string representing the `using` expression (e.g., "using 1:2", "using 4:6:8:9")
    /// @param with The string representing the `with plotstyle` expression (e.g., "lines", "linespoints", "dots")
    PlotSpecs(std::string what, std::string use, std::string with);

    /// Convert this PlotSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the legend label of the plotted element.
    auto label(std::string text) -> PlotSpecs&
    {
        m_title = "'" + text + "'";
        return *this;
    }

    /// Set the legend label of the plotted element to be retrieved from the header of column.
    auto labelFromColumnHeader() -> PlotSpecs&
    {
        m_title = "columnheader";
        return *this;
    }

    /// Set the legend label of the plotted element to be retrieved from the header of a column with given index.
    auto labelFromColumnHeader(int icolumn) -> PlotSpecs&
    {
        m_title = "columnheader(" + std::to_string(icolumn) + ")";
        return *this;
    }

    /// Set the legend label of the plotted element to be ignored.
    auto labelNone() -> PlotSpecs&
    {
        m_title = "notitle";
        return *this;
    }

    /// Set the legend label to be determined automatically from the plot expression.
    auto labelDefault() -> PlotSpecs&
    {
        m_title = "";
        return *this;
    }

    /// Set the column in the data file containing the tic labels for *x* axis.
    auto xtics(ColumnIndex icol) -> PlotSpecs&
    {
        m_xtic = "xtic(stringcolumn(" + icol.value + "))"; // xtic(stringcolumn(1)) or xtic(stringcolumn('Name'))
        return *this;
    }

    /// Set the column in the data file containing the tic labels for *y* axis.
    auto ytics(ColumnIndex icol) -> PlotSpecs&
    {
        m_ytic = "ytic(stringcolumn(" + icol.value + "))"; // ytic(stringcolumn(1)) or ytic(stringcolumn('Name'))
        return *this;
    }

  private:
    /// The string representing `what` to be plot (e.g., "'filename'", "sin(x)").
    std::string m_what;

    /// The string representing the `using` expression (e.g., "using 1:2", "using 4:6:8:9").
    std::string m_using;

    /// The string representing the `with plotstyle` expression (e.g., "lines", "linespoints", "dots").
    std::string m_with;

    /// The title of the plot as a gnuplot formatted string (e.g., "title 'sin(x)'").
    std::string m_title;

    /// The column in the data file containing the x tic labels.
    std::string m_xtic;

    /// The column in the data file containing the y tic labels.
    std::string m_ytic;
};

PlotSpecs::PlotSpecs(std::string what, std::string use, std::string with)
: m_what(what), m_using(use), m_with(with)
{
    lineWidth(internal::DEFAULT_LINEWIDTH);
}

auto PlotSpecs::repr() const -> std::string
{
    std::string use = m_using;
    use += ":" + m_xtic + ":" + m_ytic;
    use = internal::trimright(use, ':'); // remove any leading `:` in string `use`

    std::stringstream ss;
    ss << m_what << " ";
    ss << gnuplot::optionValueStr("using", use);
    ss << gnuplot::optionValueStr("title", m_title);
    ss << gnuplot::optionValueStr("with", m_with);
    ss << LineSpecsOf<PlotSpecs>::repr() << " ";
    ss << PointSpecsOf<PlotSpecs>::repr() << " ";
    ss << FillSpecsOf<PlotSpecs>::repr() << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
