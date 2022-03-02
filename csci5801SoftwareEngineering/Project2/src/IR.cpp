#include "../src/IR.h"

IR::IR(std::string type, int candidates, int seats, int ballots) {
  electionType = type;
  numCandidates = candidates;
  numSeats = seats;
  numBallots = ballots;
}

void IR::findWinner() {
  sortedCandidates = candidates;
  tiedCandidates = {};
  std::sort(sortedCandidates.begin(), sortedCandidates.end());
  std::reverse(sortedCandidates.begin(), sortedCandidates.end());
  if (sortedCandidates.at(0).getNumBallots() * 2 >
      numBallots) {  // if majority, winner found
    writeToAuditFile("Checking for a majority.\n");
    addWinners(sortedCandidates.at(0));
    writeToAuditFile(sortedCandidates.at(0).getName() +
                     " has a majority and has won the election.\n");
  } else {
    int i = sortedCandidates.size() - 1;
    while (!sortedCandidates.at(i).getNumBallots() && i) {
      i--;
    }
    tiedCandidates.push_back(sortedCandidates.at(i--));
    while (i >= 0 && tiedCandidates.at(0).getNumBallots() ==
               sortedCandidates.at(i).getNumBallots()) {
      tiedCandidates.push_back(sortedCandidates.at(i--));
    }
    breakTie();
  }
}

void IR::elimination() {
  for (int i = elim->getNumBallots() - 1; i >= 0; i--) {
    writeToAuditFile("Incremented a ballot.\n");
    elim->getBallots()
        .at(i)
        .incrCurrent();  // Increment every ballot from that candidate
    Ballot ballot = elim->getBallots().at(i);
    while (ballot.getCurrBallotIndex() >= 0 &&
           (candidates[ballot.getCurrBallotIndex()].getNumBallots() == 0) &&
           (ballot.getCurrBallot() < candidates.size() - 1)) {
      // ensures the ballot index is non-negative and that there exists another
      // candidate to vote for

      // ensures that the candidate we're giving it too isn't out of the race
      // (i.e. has 0 ballots)

      // ensures we don't over increment the ballot
      writeToAuditFile(
          candidates[ballot.getCurrBallotIndex()].getName() +
          " was eliminated earlier and this ballot will be incremented.\n");
      ballot.incrCurrent();
    }

    if (ballot.getCurrBallotIndex() >= 0) {
      candidates[ballot.getCurrBallotIndex()].addBallot(ballot);
      writeToAuditFile(candidates[ballot.getCurrBallotIndex()].getName() +
                       " has gained a ballot.\n");
    }
    // Inside each ballot, getCurrBallotIndex takes in the current index of the
    // Ballot and returns The value corresponding to the next highest voted
    // candidiate in that ballot. That value represents the position of the
    // candidate in the candidates vector.
    // elim->getBallots()[i] = a ballot
    // getCurrBallotIndex() = the candidate index ( not the ballot)
    // candidates[elim->getBallots()[i].getCurrBallotIndex()] = Specific
    // candidate addBallot(elim->getBallots()[i]) = take current ballot and add
    // to that candidate.
  }
  std::vector<Ballot> noBallots{};
  elim->setBallots(noBallots);
  writeToAuditFile(elim->getName() + " has been eliminated.\n");
}

void IR::breakTie() {
  srand(time(NULL));
  int random = rand() % tiedCandidates.size();
  elim = &tiedCandidates.at(random);
  writeToAuditFile(
      elim->getName() +
      " has lost the tiebreaker and is now in line to be eliminated.\n");
}

void IR::checkIfOneCand() {
  int flag = -1;
  int index = 0;
  for (int i = 0; i < candidates.size(); i++) {
    if (candidates[i].getNumBallots() != 0) {
      flag++;
      index = i;
    }
  }
  if (!flag) {
    writeToAuditFile("There is only one candidate left. " +
                     candidates[index].getName() + " has won!");
    addWinners(candidates[index]);
  }
}

void IR::runElection() {
  makeAuditFile();
  for (int j = 0; j < candidates.size(); j++) {
    writeToAuditFile("Initialization: " + candidates[j].getName() + " has " +
                     std::to_string(candidates[j].getNumBallots()) +
                     " ballots.\n");
    candidates[j].setInitBallots(candidates[j].getNumBallots());
  }
  findWinner();
  while (winners.size() == 0) {
    elimination();
    checkIfOneCand();
    if (winners.size() == 0) findWinner();
  }
  for (int i = 0; i < candidates.size(); i++) {
    if (candidates[i].getName() != winners[0].getName()) {
      writeToAuditFile(candidates[i].getName() +
                       " has been added to the losers.");
      addLosers(candidates[i]);
    }
  }
  makeMediaFile();
}

void IR::printCandidateInfo() {
  for (int i = 0; i < candidates.size(); i++) {
    std::cout << "name: " << candidates[i].getName() << std::endl;
    std::cout << "numBallots: " << candidates[i].getNumBallots() << std::endl;
  }
  std::cout << "end print" << std::endl;
}

void IR::displayResults() {
  std::cout << "General Election Information" << std::endl;
  printf("\tElection Type: IR\n");
  printf("\tTotal Ballots: %d\n", numBallots);
  writeToMediaFile(
      "Election Type: IR\nTotal Ballots:" + std::to_string(numBallots) + "\n");

  std::cout << "\nWinner" << std::endl;
  writeToMediaFile("Winner\n");
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  for (int i = 0; i < winners.size(); i++) {
    printf("\t%-60s %-15c %-d\n", winners[i].getName().c_str(),
           winners[i].getParty(), winners[i].getInitBallots());
    writeToMediaFile("Name: " + winners[i].getName() +
                     " Party: " + std::string(1, winners[i].getParty()) +
                     " Votes: " + std::to_string(winners[i].getNumBallots()) +
                     "\n");
  }

  std::cout << "\nLosers\n" << std::endl;
  writeToMediaFile("Loser(s)\n");
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  for (int i = 0; i < losers.size(); i++) {
    printf("\t%-60s %-15c %-d\n", losers[i].getName().c_str(),
           losers[i].getParty(), losers[i].getInitBallots());
    writeToMediaFile("Name: " + losers[i].getName() +
                     " Party: " + std::string(1, losers[i].getParty()) +
                     " Votes: " + std::to_string(losers[i].getInitBallots()) +
                     "\n");
  }
}
