#include <iostream>
#include <string>
#include <map>

class Team {
public:
    static int totalTeams;  

    // Constructor 
    
    Team(int id, const std::string& name, const std::string players[], int numPlayers)
        : ID(id), name(name), wins(0), losses(0) {
        for (int i = 0; i < numPlayers; ++i) {
            this->players[i] = players[i];
         }
        this->numPlayers =  numPlayers;
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
    } //Destructor

private:
    int ID;
    std::string name;
    std::string players[10];
    int numPlayers;
    int wins;
    int losses;



};

int Team::totalTeams = 0;  

class Match {
public:
    static int totalMatchesPlayed;  

    Match() : ID(0) {}
    Match(int id, Team& team1, Team& team2)
        : ID(id), teams(std::make_pair(&team1, &team2)), status("scheduled") {
        score[team1.getName()] = 0;
        score[team2.getName()] = 0;
    }

    // Accessor and mutator methods
    int getID() const { return ID; }  // Accessor for match ID
    std::string getStatus() const { return status; }  // Accessor for match status
    void updateStatus(const std::string& newStatus) { status = newStatus; }  // Mutator for match status

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
    } //Destructor

private:
    int ID;
    std::pair<Team*, Team*> teams;
    std::map<std::string, int> score;
    std::string status;
};

int Match::totalMatchesPlayed = 0;  

int main() {
    Team teams[2] = {
        Team(1, "Team A", new std::string[2]{"Player 1", "Player 2"}, 2),
        Team(2, "Team B", new std::string[2]{"Player 3", "Player 4"}, 2)
    };

    // Using mutator method to update the team name
    teams[0].updateTeamName("Strikers");

    // Registering teams
    for (int i = 0; i < 2; ++i) {
        teams[i].registerTeam();
    }

    std::cout << "Total teams registered: " << Team::getTotalTeams() << std::endl;

    // Creating and scheduling a match
    Match* matches = new Match[1];
    matches[0] = Match(101, teams[0], teams[1]);

    matches[0].schedule("2024-07-30");
    matches[0].play();

    std::cout << "Total matches played: " << Match::getTotalMatchesPlayed() << std::endl;

    // Updating team stats
    teams[0].updateStats(true);
    teams[1].updateStats(false);

    // Using accessor methods to retrieve data
    std::cout << teams[0].getName() << " has " << teams[0].getWins() << " wins and " << teams[0].getLosses() << " losses." << std::endl;
    std::cout << teams[1].getName() << " has " << teams[1].getWins() << " wins and " << teams[1].getLosses() << " losses." << std::endl;

    delete[] matches;
    return 0;
}
