# MinUI

## What is this?

MinUI is a minimalist X11 GUI toolkit.

MinUI aims to be easy to use, light-weight and low-dependency, as well as proposing an original approach to GUI design.

<p align="center">
  <img src="https://github.com/Cryst4L/MinUI/blob/master/demo.gif"/>
</p>

##How it works

In MinUI every widget belongs to a canva, which is a widget storage affected to a rectangular part of the screen.

As canvas can contain other canvas, the set of all canvas is structured as a tree, starting from the canva 'root'.

Every widget is declared with an 'id', which is used to retreive the widget from the canva tree.

The widget memory management is automated and opaque.

To reduce the size of magic numbers, all the positions are given relatively to a grid. The grid size being a global constant which is used in the drarwing primitives.

*More details incoming*

## Copyright

This project is released under MIT license.

```
MIT License

Copyright (c) 2016-2021, Benjamin D. Halimi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
