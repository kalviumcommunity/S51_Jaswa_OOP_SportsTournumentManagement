#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

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

    virtual void displayTeamInfo() const = 0;

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

// Base Match class
class Match {
public:
    static int totalMatchesPlayed;

    Match(int id, Team& team1, Team& team2)
        : ID(id), teams(std::make_pair(&team1, &team2)), status("scheduled") {
        score[team1.getName()] = 0;
        score[team2.getName()] = 0;
    }

    virtual void play() {
        status = "completed";
        totalMatchesPlayed++;
        std::cout << "Match " << ID << " played." << std::endl;
    }

    virtual ~Match() {
        std::cout << "Destructor called for Match " << ID << std::endl;
    }

protected:
    int ID;
    std::pair<Team*, Team*> teams;
    std::map<std::string, int> score;
    std::string status;
};

int Match::totalMatchesPlayed = 0;

// Derived class from Match: LeagueMatch
class LeagueMatch : public Match {
public:
    LeagueMatch(int id, Team& team1, Team& team2, const std::string& leagueName)
        : Match(id, team1, team2), leagueName(leagueName) {}

    void play() override {
        Match::play();
        std::cout << "This is a league match in " << leagueName << " league." << std::endl;
    }

private:
    std::string leagueName;
};

// Derived class from Match: TournamentMatch
class TournamentMatch : public Match {
public:
    TournamentMatch(int id, Team& team1, Team& team2, const std::string& tournamentName)
        : Match(id, team1, team2), tournamentName(tournamentName) {}

    void play() override {
        Match::play();
        std::cout << "This is a tournament match in " << tournamentName << " tournament." << std::endl;
    }

private:
    std::string tournamentName;
};

int main() {
    // Creating players
    std::vector<Player> teamAPlayers = {Player("Player 1"), Player("Player 2")};
    std::vector<Player> teamBPlayers = {Player("Player 3"), Player("Player 4")};

    // Creating teams
    LeagueTeam teamA(1, "Team A", teamAPlayers, "Premier League");
    LeagueTeam teamB(2, "Team B", teamBPlayers, "Premier League");

    // Creating and scheduling matches
    Schedule schedule;
    schedule.scheduleMatch(101, "2024-07-30");

    // Using polymorphism to play matches
    std::vector<std::unique_ptr<Match>> matches;
    matches.push_back(std::make_unique<LeagueMatch>(101, teamA, teamB, "Premier League"));
    matches.push_back(std::make_unique<TournamentMatch>(102, teamA, teamB, "Champions Cup"));

    for (const auto& match : matches) {
        match->play();
    }

    std::cout << "Total matches played: " << Match::getTotalMatchesPlayed() << std::endl;

    return 0;
}
