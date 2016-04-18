# Quad-Tree-Data-Compression
The region quadtree represents a partition of space in two dimensions by decomposing the region into four equal quadrants, sub-quadrants, and so on with each leaf node containing data corresponding to a specific sub-region. Each node in the tree either has exactly four children, or has no children (a leaf node).

A region quadtree with a depth of n may be used to represent an image consisting of 2n × 2n pixels, where each pixel value is 0 or 1. The root node represents the entire image region. If the pixels in any region are not entirely 0s or 1s, it is subdivided. In this application, each leaf node represents a block of pixels that are all 0s or all 1s.

Regions are subdivided until each leaf contains at most a single point.
## Notes
This program demonstrates the compression of a given input file using Quad-Tree data compression
The initial 'image' used as an example is within qtdata.txt
A resulting 113 nodes were created upon compression
