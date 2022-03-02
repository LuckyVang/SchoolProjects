/**
 * @file OPL.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */

#ifndef OPL_H
#define OPL_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

#include "../src/Party.h"
#include "../src/VotingSystem.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing the OPL Voting System, used to run an OPL
 * election results.
 *
 */
class OPL : public VotingSystem {
 public:
  /**
   * @brief Constructor for PO. Sets type of election, number of candidates,
   * number of seats, and number of ballots.
   */
  OPL(std::string type, int candidates, int seats, int ballots);

  /**
   * @brief Sorts parties vector by number of votes.
   */
  void sortByVotes();

  /**
   * @brief Sorts parties vector by remainder.
   */
  void sortByRemainder();

  /**
   * @brief Gives Seats to parties.
   *
   * Sorts the parties by number of votes and then allocates the amount of seats
   * by the amount of votes that they got divided by the quota.
   * This is done twice. The first passthrough is just dividing by quota.
   * The second passthrough is to distribute remaining votes.
   *
   * @return void.
   */
  void allocateSeats();

  /**
   * @brief Add winners to winners vector.
   *
   * Goes through every party and adds the top of each party
   * to the winners vector depending on the amount of seats
   * each party has.
   *
   * @return void.
   */
  void findPartyWinners();

  /**
   * @brief Runs the OPL election.
   *
   * Runs all of the methods needed to run a OPL election.
   *
   * @return void.
   */
  void runElection();

  /**
   * @brief Prints the results of the election.
   *
   * Displays all the information an election official would need in an
   * election. Such information includes: Number of Ballots Winners Losers
   * Election Type
   *
   * @return void.
   */
  void displayResults();

  /**
   * @brief A setter for parties.
   *
   * Sets the parties vector
   */
  void setParties(std::vector<Party> parties_);

  /**
   * @brief A setter for quota.
   *
   * Sets the quota
   */
  void setQuota(int n) { quota = n; }

  /**
   * @brief A setter for numSeats.
   *
   * Sets the numSeats
   */
  void setNumSeats(int n) { numSeats = n; }

  /**
   * @brief Prints information about each Party for debugging purposes.
   */
  void printPartyInfo();
  /**
   * @brief Adds the votes from each member in a party to the party. Does this for every party.
   */
  void addVotesPerParty();

 private:
  int quota;  ///< numVotes / numSeats. Used to find how many seats each party
              ///< gets.
};

#endif
