#include <iostream>
#include <string>
#include <map>

// Base class: Team
class Team {
public:
    static int totalTeams;

    // Constructor
    Team(int id, const std::string& name, const std::string players[], int numPlayers)
        : ID(id), name(name), wins(0), losses(0) {
        for (int i = 0; i < numPlayers; ++i) {
            this->players[i] = players[i];
        }
        this->numPlayers = numPlayers;
        totalTeams++;
    }

    // Accessor and mutator methods
    int getID() const { return ID; }
    std::string getName() const { return name; }
    void updateTeamName(const std::string& newName) { name = newName; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }

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

    static int getTotalTeams() {
        return totalTeams;
    }

    ~Team() {
        std::cout << "Destructor called for Team " << name << std::endl;
    }

private:
    int ID;
    std::string name;
    std::string players[10];
    int numPlayers;
    int wins;
    int losses;
};

int Team::totalTeams = 0;

// Derived class from Team: LeagueTeam (Single Inheritance)
class LeagueTeam : public Team {
public:
    LeagueTeam(int id, const std::string& name, const std::string players[], int numPlayers, const std::string& league)
        : Team(id, name, players, numPlayers), league(league) {}

    std::string getLeague() const { return league; }
    void updateLeague(const std::string& newLeague) { league = newLeague; }

private:
    std::string league;
};

// Derived class from LeagueTeam: TournamentTeam (Multilevel Inheritance)
class TournamentTeam : public LeagueTeam {
public:
    TournamentTeam(int id, const std::string& name, const std::string players[], int numPlayers, const std::string& league, const std::string& tournament)
        : LeagueTeam(id, name, players, numPlayers, league), tournament(tournament) {}

    std::string getTournament() const { return tournament; }
    void updateTournament(const std::string& newTournament) { tournament = newTournament; }

private:
    std::string tournament;
};

// Match class remains unchanged
class Match {
public:
    static int totalMatchesPlayed;

    Match() : ID(0) {}
    Match(int id, Team& team1, Team& team2)
        : ID(id), teams(std::make_pair(&team1, &team2)), status("scheduled") {
        score[team1.getName()] = 0;
        score[team2.getName()] = 0;
    }

    int getID() const { return ID; }
    std::string getStatus() const { return status; }
    void updateStatus(const std::string& newStatus) { status = newStatus; }

    void schedule(const std::string& date) {
        std::cout << "Match " << ID << " between " << teams.first->getName() << " and " << teams.second->getName() << " scheduled for " << date << "." << std::endl;
    }

    void play() {
        status = "completed";
        totalMatchesPlayed++;
        std::cout << "Match " << ID << " between " << teams.first->getName() << " and " << teams.second->getName() << " played." << std::endl;
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
    // Creating TournamentTeam objects (Multilevel Inheritance)
    TournamentTeam teamA(1, "Team A", new std::string[2]{"Player 1", "Player 2"}, 2, "Premier League", "Champions Cup");
    TournamentTeam teamB(2, "Team B", new std::string[2]{"Player 3", "Player 4"}, 2, "Premier League", "Champions Cup");

    // Register teams
    teamA.registerTeam();
    teamB.registerTeam();

    std::cout << "Team A is in " << teamA.getLeague() << " and participating in " << teamA.getTournament() << std::endl;
    std::cout << "Team B is in " << teamB.getLeague() << " and participating in " << teamB.getTournament() << std::endl;

    // Scheduling and playing a match
    Match match1(101, teamA, teamB);
    match1.schedule("2024-07-30");
    match1.play();

    std::cout << "Total matches played: " << Match::getTotalMatchesPlayed() << std::endl;

    return 0;
}
