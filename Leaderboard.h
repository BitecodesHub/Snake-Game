#pragma once
#include <string>
#include <vector>

struct ScoreEntry {
    std::string name;
    int score;
};

class Leaderboard {
public:
    Leaderboard(const std::string& path = "leaderboard.json");
    void load();
    void save();
    void add(const std::string& name, int score);
    std::vector<ScoreEntry> top(int n = 10) const;
private:
    std::string path_;
    std::vector<ScoreEntry> entries_;
};
