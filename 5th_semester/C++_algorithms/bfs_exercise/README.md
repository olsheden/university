Program Interface
Your task is to implement a function std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths), which finds the longest possible track for a downhill skiing race on the given map. The track can start and end at any intersection. The parameters are the number of intersections points and a list of usable paths between intersections all_paths. Each path contains a starting intersection from and a destination to and can only be traversed in this direction, as all segments must lead downhill. It also contains the length of the given path length. The length is always a non-negative integer.

The output is a list of consecutive paths (i.e., the destination of one path is the starting point of the next one) that form the longest possible track. If there are multiple longest tracks, any of them can be returned.

You can assume that the input is always valid, meaning:

Intersections where paths start and end are within the range [0, points).
All paths lead downhill.