#include <iostream>
#include <string>
#include <vector>
#include <map>

// Player class for managing individual player details
class Player {
public:
    Player(const std::string& name) : name(name) {}

    std::string getName() const { return name; }

private:
    std::string name;
};

// TeamStatistics class for tracking wins and losses
class TeamStatistics {
public:
    void updateStats(bool win) {
        if (win) {
            wins++;
        } else {
            losses++;
        }
        std::cout << "Updated stats: " << wins << " wins, " << losses << " losses." << std::endl;
    }

    int getWins() const { return wins; }
    int getLosses() const { return losses; }

private:
    int wins = 0;
    int losses = 0;
};

// Abstract class: Team
class Team {
public:
    static int totalTeams;

    Team(int id, const std::string& name, const std::vector<Player>& players)
        : ID(id), name(name), players(players) {
        totalTeams++;
    }

    virtual void displayTeamInfo() const = 0; // Abstract method

    std::string getName() const { return name; }
    TeamStatistics& getStatistics() { return statistics; }

    virtual ~Team() {
        std::cout << "Destructor called for Team " << name << std::endl;
    }

protected:
    int ID;
    std::string name;
    std::vector<Player> players;
    TeamStatistics statistics;
};

int Team::totalTeams = 0;

// Derived class from Team: LeagueTeam (Single Inheritance)
class LeagueTeam : public Team {
public:
    LeagueTeam(int id, const std::string& name, const std::vector<Player>& players, const std::string& league)
        : Team(id, name, players), league(league) {}

    void displayTeamInfo() const override {
        std::cout << "League Team " << getName() << " is in the league: " << league << std::endl;
    }

private:
    std::string league;
};

// Schedule class for managing match scheduling
class Schedule {
public:
    void scheduleMatch(int matchID, const std::string& date) {
        matchDates[matchID] = date;
        std::cout << "Match " << matchID << " scheduled for " << date << "." << std::endl;
    }

    std::string getMatchDate(int matchID) const {
        auto it = matchDates.find(matchID);
        return it != matchDates.end() ? it->second : "Date not found";
    }

private:
    std::map<int, std::string> matchDates;
};

// Match class with Constructor Overloading (Polymorphism)
class Match {
public:
    static int totalMatchesPlayed;

    Match(int id, Team& team1, Team& team2)
        : ID(id), teams(std::make_pair(&team1, &team2)), status("scheduled") {
        score[team1.getName()] = 0;
        score[team2.getName()] = 0;
    }

    Match(int id) : ID(id), status("pending teams") {}

    void play() {
        status = "completed";
        totalMatchesPlayed++;
        std::cout << "Match " << ID << " played." << std::endl;
    }

    static int getTotalMatchesPlayed() {
        return totalMatchesPlayed;
    }

    ~Match() {
        std::cout << "Destructor called for Match " << ID << std::endl;
    }

private:
    int ID;
    std::pair<Team*, Team*> teams;
    std::map<std::string, int> score;
    std::string status;
};

int Match::totalMatchesPlayed = 0;

int main() {
    // Creating players
    std::vector<Player> teamAPlayers = {Player("Player 1"), Player("Player 2")};
    std::vector<Player> teamBPlayers = {Player("Player 3"), Player("Player 4")};

    // Creating teams
    LeagueTeam teamA(1, "Team A", teamAPlayers, "Premier League");
    LeagueTeam teamB(2, "Team B", teamBPlayers, "Premier League");

    // Displaying team info
    teamA.displayTeamInfo();
    teamB.displayTeamInfo();

    // Creating and scheduling matches
    Schedule schedule;
    schedule.scheduleMatch(101, "2024-07-30");

    // Playing a match
    Match match1(101, teamA, teamB);
    match1.play();

    std::cout << "Total matches played: " << Match::getTotalMatchesPlayed() << std::endl;

    return 0;
}
