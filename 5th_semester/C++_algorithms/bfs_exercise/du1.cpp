#ifndef __PROGTEST__
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {};

struct Path {
    Point from, to;
    unsigned length;

    Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

    friend bool operator == (const Path& a, const Path& b) {
        return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
    }

    friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

#endif

std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){
    std::vector<size_t> Prev(points, -size_t(1));
    std::vector<size_t> Dist(points, -size_t(2));
    std::vector<size_t> srcs_cnt(points, 0);
    std::queue<Point> q;
    std::vector<std::vector<std::pair<Point, unsigned>>> map(points);
    for(const auto & path : all_paths){
        srcs_cnt[path.to]++;
        map[path.from].emplace_back(path.to, path.length);
    }
    for(size_t i = 0; i < srcs_cnt.size(); i++){
        if(srcs_cnt[i] == 0) {
            q.push(Point{i});
            Dist[i] = 0;
        }
    }
    std::pair<Point, size_t> res = std::make_pair(Point{size_t{0}}, -size_t(1));
    bool flag = false;
    while(!q.empty()){
        Point tmp = q.front();
        q.pop();
        flag = false;
        for(const auto & nbr : map[tmp]){
            flag = true;
            if((Dist[nbr.first] == -size_t(2)) || (Dist[nbr.first] < (Dist[tmp] + nbr.second))) {
                Dist[nbr.first] = (Dist[tmp] + nbr.second);
                Prev[nbr.first] = tmp;
                q.push(nbr.first);
            }
        }
        if (!flag) {
            if(res.second == -size_t(1) || res.second < Dist[tmp]) res = {tmp, Dist[tmp]};
        }
    }
    Point max_point = res.first;
    std::vector<Path> res_list;
    while(Prev[max_point] != -size_t(1)){
        res_list.emplace_back(Prev[max_point], max_point, Dist[max_point] - Dist[Prev[max_point]]);
        max_point = Point{Prev[max_point]};
    }
    std::reverse(res_list.begin(), res_list.end());

    return res_list;

}


#ifndef __PROGTEST__


struct Test {
    unsigned longest_track;
    size_t points;
    std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
        {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
        {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
        {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
    auto sol = longest_track(t.points, t.all_paths);

    unsigned length = 0;
    for (auto [ _, __, l ] : sol) length += l;

    CHECK(t.longest_track == length,
          "Wrong length: got %u but expected %u", length, t.longest_track);

    for (size_t i = 0; i < sol.size(); i++) {
        CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
              "Solution contains non-existent path: %zu -> %zu (%u)",
              sol[i].from, sol[i].to, sol[i].length);

        if (i > 0) CHECK(sol[i].from == sol[i-1].to,
                         "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
    }

    return true;
}
#undef CHECK

int main() {
    int ok = 0, fail = 0;

    for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;

    if (!fail) printf("Passed all %i tests!\n", ok);
    else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif


