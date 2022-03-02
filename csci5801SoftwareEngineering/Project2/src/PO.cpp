#include "../src/PO.h"
#include <algorithm>

PO::PO(int candidates) {
  numCandidates = candidates;
  numBallots = 0;
}

void PO::runElection() {
  std::sort(candidates.begin(), candidates.end());
  std::reverse(candidates.begin(), candidates.end());
  breakTie();
}

void PO::breakTie() {
  int i = 0;
  while (candidates[0].getNumBallots() == candidates[i++].getNumBallots());
  if (--i) {
    srand (time(NULL));
    iter_swap(candidates.begin(), candidates.begin() + rand() % i);
  }
}

void PO::displayResults() {
  std::cout << "General Election Information" << std::endl;
  printf("\tElection Type: PO\n");
  printf("\tTotal Ballots: %d\n", numBallots);
  writeToMediaFile("Election Type: PO\n");
  writeToMediaFile("Total Ballots: " + std::to_string(numBallots));
  std::cout << "\nWinner" << std::endl;
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  writeToMediaFile("Winner:\n");
  writeToAuditFile("Winner:\n");
  writeToAuditFile("Name: " + candidates.at(0).getName() + " Party: " +
                   std::string(1, candidates.at(0).getParty()) + " Votes: " +
                   std::to_string(candidates.at(0).getNumBallots()) + "\n");
  writeToMediaFile("Name: " + candidates.at(0).getName() + " Party: " +
                   std::string(1, candidates.at(0).getParty()) + " Votes: " +
                   std::to_string(candidates.at(0).getNumBallots()) + "\n");
  printf("\t%-60s %-15c %-d\n", candidates.at(0).getName().c_str(),
         candidates.at(0).getParty(), candidates.at(0).getNumBallots());

  std::cout << "\nLosers\n" << std::endl;
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  writeToMediaFile("Losers:\n");
  for (int i = 1; i < candidates.size(); i++) {
    writeToMediaFile("Name: " + candidates[i].getName() + " Party: " +
                     std::string(1, candidates[i].getParty()) + " Votes: " +
                     std::to_string(candidates[i].getNumBallots()) + "\n");
    printf("\t%-60s %-15c %-d\n", candidates[i].getName().c_str(),
           candidates[i].getParty(), candidates[i].getNumBallots());
  }
}