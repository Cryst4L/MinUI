# MinUI

## What is this?

MinUI is a minimalist X11 GUI toolkit implemented in C++98.
MinUI aims to be easy to use, lightweight and have no dependencies excepted 'pthread'. 
It also aims to propose an original approach to GUI design.

<p align="center">
  <img src="https://github.com/Cryst4L/MinUI/blob/master/demo.gif"/>
</p>

## How it works

### Apps

The recommended way to design a MinUI interface is to implement an App that is derived from MinUI::App. 

```cpp
class MyApp : public MinUI::App
{
  public :
	void init() {}
	void update() {}
};

```
Then the programmer will have to override the 'init()' and 'update()' methods.

### Canvas

In a MinUI interface, every widget belongs to a canvas. 
A canvas is a widget storage affected to a rectangular part of the screen.
A canvas can contain other smaller canvas. 
As a consequence the set of all canvas is structured as a tree, starting from the canvas 'root'.

To declare a widget, for example a button, inside the root canvas you can do the following:
```cpp
canvas("root").addButton("reset", "RESET", {10.5, 10}, {5, 2})
```
To declare another canvas inside the root canvas you can do:
```cpp
canvas("root").addCanva("button", { 0, 0}, {9.5, 1}, "");
```
This (quite obviously) also works for any other canvas.

### IDs

Every widget is declared with an 'id'. This 'id' is used to retrieve the widget from the canvas tree.

In the method 'update' once can retrieve a widget, for example a button, by calling it in the following way: 

```cpp
button("my_button_id");
```

Then the programmer can act on the widget, by using the widget available methods. Here is an example:

```cpp
if (button("reset").isClicked())
	variable = 0; 
```
### The Grid

In a MinUI interface all the positions are given by constants, according to their belonging canvas.
This means that MinUI interfaces are not responsive, but on the other hand, it ensures that the interface will look exactly like the programmer will.

A major issue in such approaches is the management of large 'magic numbers', which encode the positions and size of the widgets.
To address this issue every magic number is expressed according to a fixed size, just as if they were placed on a grid.
By default the grid size is of 25 pixels. 

### Threading

MinUI was developed with multithreading in mind. 
The goal was to propose an API which allows the management of multiple panels (or Apps) at the same time.

Once the programmer has implemented its own App, he can either launch it using the 'run' method:
```cpp
myapp.run();
```
In that case the App will occupy the main thread and will be blocking.
But MinUI also proposes to run the App in its own thread, letting the main thread untouched.
Launching an App in its own thread, is very simple. It is done using the 'start' method (instead of the 'run' one).
In that case the programmer will also have to call the 'stop' method to close the thread. Here is a full example:
```cpp
MyApp app;
app.start();
app.join();
```
### Memory

The widget memory management is automated and opaque. 
There is no need to 'new' or 'delete' anything.
This is a major feature of MinUI considering that it is written in C++98.

### Example

There is a complete example in the corresponding folder. To build it, you want to open a terminal in the root '/MinUI' folder and write the following commands:

```sh
mkdir build && cd build
cmake ..
make
```
The executable will be stored in the 'build' directory. 

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
