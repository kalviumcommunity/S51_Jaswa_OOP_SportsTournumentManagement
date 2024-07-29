#include <iostream>
#include <vector>
#include <string>
#include<map>

// Team class definition
class Team {
public:
    Team(int id, const std::string& name, const std::vector<std::string>& players)
        : ID(id), name(name), players(players), wins(0), losses(0) {}

    void registerTeam() {
        std::cout << "Team " << name << " registered with ID " << ID << "." << std::endl;
    }

    void updateStats(bool win) {
        if (win) {
            wins++;
        } else {
            losses++;
        }
        std::cout << "Team " << name << " stats updated: " << wins << " wins, " << losses << " losses." << std::endl;
    }

    std::string getName() const {
        return name;
    }

    void updateTeamName(std::string name){
        this->name = name;
    }



private:
    int ID;
    std::string name;
    std::vector<std::string> players;
    int wins;
    int losses;
};


class Match {
public:
    Match(int id, Team& team1, Team& team2)
        : ID(id), teams(std::make_pair(&team1, &team2)), status("scheduled") {
        score[team1.getName()] = 0;
        score[team2.getName()] = 0;
    }

    void schedule(const std::string& date) {
        std::cout << "Match " << ID << " between " << teams.first->getName() << " and " << teams.second->getName() << " scheduled for " << date << "." << std::endl;
    }

    void play() {
        status = "completed";
        std::cout << "Match " << ID << " between " << teams.first->getName() << " and " << teams.second->getName() << " played." << std::endl;
    }

private:
    int ID;
    std::pair<Team*, Team*> teams;
    std::map<std::string, int> score;
    std::string status;
};
int main() {
    Team team1(1, "Team A", {"Player 1", "Player 2"});
    Team team2(2, "Team B", {"Player 3", "Player 4"});
    team1.updateTeamName("Strikers");
    team1.registerTeam();
    team2.registerTeam();

    Match match1(101, team1, team2);

    match1.schedule("2024-07-30");
    match1.play();

    team1.updateStats(true);
    team2.updateStats(false);

    return 0;
}
