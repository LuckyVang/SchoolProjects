/**
 * @file VotingSystem.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */

#ifndef VOTINGSYSTEM_H
#define VOTINGSYSTEM_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdlib.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../src/Ballot.h"
#include "../src/Candidate.h"
#include "../src/Party.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing a generic Voting System to be used for running
 * election results.
 *
 */
class VotingSystem {
 public:
  // VotingSystem(std::string type, int candidates, int seats, int ballots);

  /**
     * @brief Returns the winner vector.
     *
     * Returns the vector containing all the winners of this election.
     *
     * @return std::vector<Candidate>

    */
  std::vector<Candidate> getWinners() { return winners; };

  /**
   * @brief Returns the losing vector.
   *
   * Returns the vector containing all the losers of this election.
   *
   * @return std::vector<Candidate>
   */
  std::vector<Candidate> getLosers() { return losers; }

  /**
    * @brief Returns the number of ballots in the system..
    *
    * Returns the number of ballots in the current system which is a parameter
    * given when created.
    *
    * @return int.

   */
  int getNumBallots();

  /**
   * @brief Returns the time taken.
   *
   * Returns the amount needed to run the entire program.
   *
   * @return int.
   */
  double getTimeTaken();

  // Candidate breakTie(std::vector<Candidate>);
  /**
   * @brief Adds a winning candidate to the winners vector.
   *
   * @return void.
   */
  void addWinners(Candidate candidate);

  /**
   * @brief Adds a losing candidate to the losers vector.
   *
   * @return void.
   */
  void addLosers(Candidate candidate);

  /**
   * @brief Will be used to run elections.
   *
   * Used by inherited classes to run their respective elections.
   *
   * @return void.
   */
  virtual void runElection();

  /**
   * @brief Used to display results.
   *
   * Used by inherited classes to run display their own results.
   *
   * @return void.
   */
  virtual void displayResults();

  /**
   * @brief Creates an audit file.
   *
   * Creates a new file that will be used as an audit for the election
   *
   * @return void.
   */
  void makeAuditFile();

  /**
   * @brief Writes to the audit file.
   *
   * @param[in] string What will be written into the audit file.
   *
   * @return void.
   */
  void writeToAuditFile(std::string string);

  /**
   * @brief Makes a media file to be written to.
   *
   * @return void.
   */
  void makeMediaFile();

  /**
   * @brief Writes a message to the media file.
   *
   * @param string What will be written into the media file.
   *
   * @return void.
   */
  void writeToMediaFile(std::string string);

  /**
   * @brief Adds a Candidate to candidates vector.
   *
   * @param[in] candidate the candidate that will be added
   *
   * Takes in a candidate and then adds the candidate to the vector of
   * candidates.
   *
   * @return void.
   */
  void addCandidate(Candidate candidate);

  /**
   * @brief Adds a party to parties vector.
   *
   * @param[in] party the party that will be added
   *
   * Takes in a party and then adds the party to the vector of parties.
   *
   * @return void.
   */
  void addParty(Party party);

  /**
   * @brief Gets the vector of candidates.
   *
   * Returns the vector of candidates which contain candidates.
   *
   * @return std::vector<Candidate>.
   */
  std::vector<Candidate> &getCandidates();

  /**
   * @brief Gets the vector of parties.
   *
   * Returns the vector of parties which contain candidates.
   *
   * @return std::vector<Party>.
   */
  std::vector<Party> &getParties();

  /**
   * @brief Checks if a party exists.
   *
   * @param[in] party The party that will be checked
   * Checks through the vector of parties to see if it exists or not.
   *
   * @return bool.
   */
  bool partyExists(char party);

  /**
   * @brief Adds candidates to parties.
   *
   * Goes through every candidate and party and checks the candidate's party.
   * Then adds the candidate to that party if the party matches
   * Repeat for all of the candidates and parties.
   *
   * @return void.
   */

  void assignParty();

  /**
   * @brief Adds to the current number of ballots.
   *
   * @param[in] ballots The number of ballots to add.
   * Takes in an int and adds it to the current number of ballots.
   *
   * @return void.
   */
  void addNumBallots(int ballots) { numBallots += ballots; }

  /**
   * @brief Sets numBallots to num
   *
   * @param int, sets numBallots equal to this.
   *
   */
  void setNumBallots(int num) { numBallots = num; }

  /**
   * @brief Destructor for VotingSystem types
   */
  virtual ~VotingSystem() = default;

 protected:
  std::string electionType;  ///< Type of election being held
  int numCandidates;  ///< holds the number of Candidates running for seats
  int numSeats;       ///< holds the number of seats up for election
  int numBallots;     ///< holds the number of ballots to be processed
  double
      timeTaken;  ///< holds the amount of time taken by the program to execute
  std::vector<Candidate>
      candidates;  ///< vector to hold candidates running for a seat
  std::vector<Candidate> sortedCandidates;
  std::vector<Candidate> tiedCandidates;
  std::vector<Party>
      parties;  ///< vector to hold all parties involved with the election
  std::ofstream auditFile;    ///<
  std::string auditfilename;  ///<
  std::ofstream mediaFile;    ///<
  std::string mediafilename;  ///<

  std::vector<Candidate> winners;  ///< vector to hold all winners
  std::vector<Candidate> losers;   ///< vector to hold all losers
};
#endif
