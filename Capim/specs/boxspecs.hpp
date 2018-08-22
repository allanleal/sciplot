// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
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

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/linespecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for plotting elements with lines.
template<typename derivedspecs>
class boxspecs : public linespecs<derivedspecs>
{
public:
    /// Construct a default boxspecs instance.
    boxspecs();

    /// Convert this boxspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the active state of the box.
    auto show(bool value = true) -> derivedspecs& { m_show = value; return static_cast<derivedspecs&>(*this); }

private:
    /// The boolean flag that indicates if the grid lines for the chosen tics are shown.
    bool m_show;
};

template<typename derivedspecs>
boxspecs<derivedspecs>::boxspecs()
{
    show();
}

template<typename derivedspecs>
auto boxspecs<derivedspecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << "box " << linespecs<derivedspecs>::repr() << " ";
    return m_show ? ss.str() : "nobox";
}

} // namespace internal
} // namespace Capim