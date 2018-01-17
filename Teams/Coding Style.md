# Coding Style Guide

It is necessary for a team to be with only one coding style.

Team members are suggested to follow the Style Guide for the convinence of cross-debuging.

We may refer to Google C++ Style Guide 

# Header

```C++
#include <bits/stdc++.h>
using namespace std;
```

# Indentation
Use only spaces, and indent 2 spaces at a time.

We use spaces for indentation. Do not use tabs in your code. You should set your editor to emit spaces when you hit the tab key.


# Indexing
Use half open interval as default. If you write a function with args (begin, end), it should process [begin, end), otherwise you should tell your teammate or write a comment.

# Naming

1. function and variable names should start from lowercase
1. Use 'cnt' as abbreviation of count, e.g. 'cnt', 'ball\_cnt'
1. Type a '\_' to separate words in a variable, e.g. 'class\_count'
1. Use a term if term exists
1. Use i, j, k ONLY in loop iteration
1. Use variable name in problem statement as default, so that your team members can rapidly understand what you are typing.
1. Programs functionally, avoid objective programming. But if it's necessary, for instance, flow problems, use uppercase for the first character of all object names and class names, e.g. Flow Flow_Solver;

# Geometry

1. Use `complex<double>` as a point in 2d
