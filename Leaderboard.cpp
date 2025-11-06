#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Leaderboard::Leaderboard(const std::string& path) : path_(path) {
    load();
}

void Leaderboard::load() {
    entries_.clear();
    std::ifstream in(path_);
    if (!in.good()) return;
    try {
        json j;
        in >> j;
        for (auto &it : j) {
            ScoreEntry e;
            e.name = it.value("name", "Anon");
            e.score = it.value("score", 0);
            entries_.push_back(e);
        }
        std::sort(entries_.begin(), entries_.end(),
                  [](const ScoreEntry& a, const ScoreEntry& b){ return a.score > b.score; });
    } catch (...) {}
}

void Leaderboard::save() {
    json j = json::array();
    for (auto &e : entries_)
        j.push_back({{"name", e.name}, {"score", e.score}});
    std::ofstream out(path_);
    out << j.dump(2);
}

void Leaderboard::add(const std::string& name, int score) {
    entries_.push_back({name, score});
    std::sort(entries_.begin(), entries_.end(),
              [](const ScoreEntry& a, const ScoreEntry& b){ return a.score > b.score; });
    if (entries_.size() > 20) entries_.resize(20);
    save();
}

std::vector<ScoreEntry> Leaderboard::top(int n) const {
    std::vector<ScoreEntry> out;
    for (size_t i = 0; i < entries_.size() && (int)i < n; ++i)
        out.push_back(entries_[i]);
    return out;
}
