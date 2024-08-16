#include <iostream>
#include <string>
#include <map>

// Team class definition
class Team {
public:
    Team(int id, const std::string& name, const std::string players[], int numPlayers)
        : ID(id), name(name), wins(0), losses(0) {
        for (int i = 0; i < numPlayers; ++i) {
            this->players[i] = players[i];
        }
        this->numPlayers = numPlayers;
    }

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

    void updateTeamName(const std::string& newName){
        name = newName;
    }

private:
    int ID;
    std::string name;
    std::string players[10]; 
    int numPlayers;
    int wins;
    int losses;
};

class Match {
public:
    Match() : ID(0) {}  
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
    Team teams[2] = {
        Team(1, "Team A", new std::string[2]{"Player 1", "Player 2"}, 2),
        Team(2, "Team B", new std::string[2]{"Player 3", "Player 4"}, 2)
    };

    teams[0].updateTeamName("Strikers");

    for (int i = 0; i < 2; ++i) {
        teams[i].registerTeam();
    }

    Match* matches = new Match[1];
    matches[0] = Match(101, teams[0], teams[1]);

    matches[0].schedule("2024-07-30");
    matches[0].play();

    teams[0].updateStats(true);
    teams[1].updateStats(false);

    return 0;
}
