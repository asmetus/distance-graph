# Repository Overview

This repository contains computational tools with a focus on graph-based methods.

## Contents

### Notebooks
- **`notebooks/`** - Contains Jupyter notebooks for data visualization and graph generation.

### C++ Programs
The repository includes three C++ programs designed for data stream processing. All programs share the same input interface:

**Compilation Requirements:**
- C++20 compatible compiler
- Standard C++ libraries

**Input Specification:**
1. Two command-line arguments:
   - `N` - sliding window size (positive integer)
   - `δ` (delta) - threshold value (floating-point number)

2. Data stream via `stdin`:
   - Continuous input of numerical values
   - Programs process data in real-time as it arrives

**Program List:**
1. **counttriangles** - counts triangles
2. **countedges** - counts edges
3. **countconcomp** - counts connected components
