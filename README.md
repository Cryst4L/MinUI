# MinUI

## What is this?

MinUI is a minimalist X11 GUI toolkit.

MinUI aims to be easy to use, light-weight and low-dependency, as well as proposing an original approach to GUI design.

<p align="center">
  <img src="https://github.com/Cryst4L/MinUI/blob/master/demo.gif"/>
</p>

## How it works

In MinUI every widget belongs to a canva, which is a widget storage affected to a rectangular part of the screen.

As canvas can contain other canvas, the set of all canvas is structured as a tree, starting from the canva 'root'.

Every widget is declared with an 'id', which is used to retreive the widget from the canva tree.

The widget memory management is automated and opaque.

To reduce the size of magic numbers, all the positions are given relatively to a grid. The grid size being a global constant which is used in the drarwing primitives.

*More details incoming*

## Copyright

This project is released under MIT license.
