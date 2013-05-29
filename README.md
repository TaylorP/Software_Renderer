Software Renderer
============

A basic software rendering solution, based on the Z-Buffer algorithm. This implementation does not use the most optimal rasterization code as it needed to run on a variety of machines. More optimized rasterization done with SIMD instructions can be found in the SIMD/ sub directory.

The rasterizer implements basic vertex lighting and per-vertex attributes.