#include <vector>
#include <chrono>
#include "include/generate_graph.h"
#include "include/edmonds_karp.h"
#include "include/dinic.h"
#include "include/mpm.h"
#include "include/modified_edmonds_karp.h"
#include <fstream>
#include <iostream>

void write_to_file(const std::vector<std::vector<int>>& data, const std::string& file_name) {
    std::fstream fout(file_name, std::fstream::out);
    for (const auto& cur: data) {
        for (const auto& el : cur) {
            fout << el << ' ';
        }
        fout << '\n';
    }
}

void get_time(int n, int m, int max_weight, int s, int t, std::vector<std::vector<int>>& res) {
    auto graph = generate_graph(n, m, max_weight);
    res[0].push_back(n);

    auto start = std::chrono::steady_clock::now();
    int edmonds_res = edmonds_karp(graph.first, graph.second, s, t);
    auto finish = std::chrono::steady_clock::now();
    res[1].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());

    start = std::chrono::steady_clock::now();
    int dinic_res = dinic(graph.first, graph.second, s, t);
    finish = std::chrono::steady_clock::now();
    res[2].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());

    start = std::chrono::steady_clock::now();
    int mpm_res = mpm(graph.first, graph.second, s, t);
    finish = std::chrono::steady_clock::now();
    res[3].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());

    start = std::chrono::steady_clock::now();
    int modified_edmonds_karp_res = modified_edmonds_karp(graph.first, graph.second, s, t);
    finish = std::chrono::steady_clock::now();
    res[4].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());

    if (edmonds_res != dinic_res || edmonds_res != mpm_res || edmonds_res != modified_edmonds_karp_res) {
        std::cout << "Fail!";
        return;
    }
}

void time_test_few_edges() {
    int max_weight = 200;
    std::vector<std::vector<int>> res(5);
    for (int n = 100; n < 10001; n += 100) {
        int s = 0;
        int t = n - 1;
        int m = n * 2;
        get_time(n, m, max_weight, s, t, res);
    }
    write_to_file(res, "few_edges_test.txt");
}

void time_test_many_edges() {
    int max_weight = 200;
    std::vector<std::vector<int>> res(5);
    for (int n = 100; n < 2001; n += 20) {
        int s = 0;
        int t = n - 1;
        int m = n * n * 3 / 8;
        get_time(n , m, max_weight, s, t, res);
    }
    write_to_file(res, "many_edges_test.txt");
}

void time_test_complete_graph() {
    int max_weight = 200;
    std::vector<std::vector<int>> res(5);
    for (int n = 100; n < 2001; n += 20) {
        int s = 0;
        int t = n - 1;
        int m = n * (n -1) / 2;
        get_time(n , m, max_weight, s, t, res);
    }
    write_to_file(res, "complete_graph_test.txt");
}

void time_test_increase_num_edges() {
    int max_weight = 200;
    std::vector<std::vector<int>> res(5);
    int n = 2000;
    for (int m = 1000; m < n * (n - 1) / 2 + 1; m += 10000) {
        int s = 0;
        int t = n - 1;
        get_time(n , m, max_weight, s, t, res);
        res[0][res[0].size() - 1] = m;
    }
    write_to_file(res, "increase_num_edges_test.txt");
}
