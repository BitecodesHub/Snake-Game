#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

// Use nlohmann/json header (header-only). Make sure json.hpp is available.
// If you don't want a dependency, replace with a custom simple parser/writer.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

Leaderboard::Leaderboard(const std::string& path) : path_(path) {
    load();
}

void Leaderboard::load() {
    entries_.clear();
    std::ifstream in(path_);
    if (!in.good()) return; // no file yet
    try {
        json j;
        in >> j;
        if (!j.is_array()) return;
        for (auto &it : j) {
            ScoreEntry e;
            e.name = it.value("name", std::string("Anon"));
            e.score = it.value("score", 0);
            entries_.push_back(e);
        }
        // ensure sorted
        std::sort(entries_.begin(), entries_.end(), [](const ScoreEntry& a, const ScoreEntry& b){
            return a.score > b.score;
        });
    } catch (...) {
        // ignore parse errors
    }
}

void Leaderboard::save() {
    json j = json::array();
    for (auto &e : entries_) {
        j.push_back({{"name", e.name}, {"score", e.score}});
    }
    std::ofstream out(path_);
    out << j.dump(2);
}

void Leaderboard::add(const std::string& name, int score) {
    entries_.push_back({name, score});
    std::sort(entries_.begin(), entries_.end(), [](const ScoreEntry& a, const ScoreEntry& b){
        return a.score > b.score;
    });
    // keep top 20
    if (entries_.size() > 20) entries_.resize(20);
    save();
}

std::vector<ScoreEntry> Leaderboard::top(int n) const {
    std::vector<ScoreEntry> out;
    for (size_t i = 0; i < entries_.size() && (int)i < n; ++i) out.push_back(entries_[i]);
    return out;
}
