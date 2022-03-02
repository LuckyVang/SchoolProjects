#include "../src/OPL.h"

OPL::OPL(std::string type, int candidates, int seats, int ballots) {
  electionType = type;
  numCandidates = candidates;
  numSeats = seats;
  numBallots = ballots;
}

void OPL::sortByVotes() {
  writeToAuditFile("First Sort to allocate Seats\n");
  int i, j;
  for (i = 1; i < parties.size(); i++) {
    Party key = parties[i];
    j = i - 1;
    while (j >= 0 && parties[j].getNumBallots() < key.getNumBallots()) {
      std::string s;
      s.push_back(parties[j].getPartyName());
      s.append(" swaps with ");
      s.push_back(key.getPartyName());

      writeToAuditFile(s);
      parties[j + 1] = parties[j];
      j = j - 1;
    }
    parties[j + 1] = key;
  }
}

void OPL::sortByRemainder() {
  writeToAuditFile("Second Sort to allocate Seats\n");
  int i, j;
  for (i = 1; i < parties.size(); i++) {
    Party key = parties[i];
    j = i - 1;
    while (j >= 0 && parties[j].getRemainder() < key.getRemainder()) {
      writeToAuditFile(std::string(1, parties[j].getPartyName()) +
                       " swaps with " + std::string(1, key.getPartyName()) +
                       "\n");
      parties[j + 1] = parties[j];
      j = j - 1;
    }
    parties[j + 1] = key;
  }
}

void OPL::allocateSeats() {
  sortByVotes();
  for (int i = 0; i < parties.size(); i++) {  // For loop start for each party
    Party &currParty = parties[i];
    int seats = (int)currParty.getNumBallots() / quota;
    std::string a(1, currParty.getPartyName());
    if (currParty.getPartyMembers().size() > seats) {
      numSeats -= seats;
      currParty.setRemainder(currParty.getNumBallots() % quota);

      writeToAuditFile(a + " gets " + std::to_string(seats) +
                       " seats and the remainder is " +
                       std::to_string(currParty.getRemainder()) + "\n");
      currParty.setSeatsWon(seats);

    } else if (currParty.getPartyMembers().size() == seats) {
      numSeats -= seats;
      currParty.setRemainder(0);
      writeToAuditFile(a + " gets " + std::to_string(seats) +
                       " seats and the remainder is 0 \n");
      currParty.setSeatsWon(seats);

    } else {
      numSeats -= currParty.getPartyMembers().size();
      currParty.setRemainder(0);
      writeToAuditFile(a + " gets " +
                       std::to_string(currParty.getPartyMembers().size()) +
                       " seats and the remainder is 0 \n");
      currParty.setSeatsWon(currParty.getPartyMembers().size());
    }
  }  // For loop end
  sortByRemainder();

  int i = 0;
  while (numSeats != 0) {
    if (parties[i].getSeatsWon() != parties[i].getPartyMembers().size()) {
      parties[i].setSeatsWon(parties[i].getSeatsWon() + 1);
      writeToAuditFile(std::string(1, parties[i].getPartyName()) +
                       " gets another seat and has a total of " +
                       std::to_string(parties[i].getSeatsWon()) + " seats.");
    }
    i++;
    numSeats--;
  }
}

void OPL::findPartyWinners() {
  for (int i = 0; i < parties.size(); i++) {
    parties[i].sortByVotes();
    std::vector<Candidate *> partyMembers = parties[i].getPartyMembers();

    numSeats = parties[i].getSeatsWon();
    for (int k = 0; k < partyMembers.size(); k++) {
      if (numSeats != 0) {
        addWinners(*partyMembers[k]);
        numSeats--;
      } else {
        addLosers(*partyMembers[k]);
      }
    }
  }
}

void OPL::addVotesPerParty() {
  for (int i = 0; i < parties.size(); i++) {
    std::vector<Candidate *> partyMembers = parties[i].getPartyMembers();
    for (int j = 0; j < partyMembers.size(); j++) {
      writeToAuditFile(std::to_string(partyMembers[j]->getNumBallots()) +
                       " Ballots added to " + parties[i].getPartyName() +
                       " Party.\n");
      parties[i].setNumBallots(parties[i].getNumBallots() +
                               partyMembers[j]->getNumBallots());
    }
  }
}

void OPL::runElection() {
  makeAuditFile();
  writeToAuditFile("Audit file created\n");
  addVotesPerParty();
  quota = numBallots / numSeats;
  writeToAuditFile("Quota per seat is: " + std::to_string(quota) + "\n");
  allocateSeats();
  findPartyWinners();

  makeMediaFile();
}

void OPL::printPartyInfo() {
  for (int i = 0; i < parties.size(); i++) {
    std::cout << "name: " << parties[i].getPartyName() << std::endl;
    std::cout << "numBallots: " << parties[i].getNumBallots() << std::endl;
    std::cout << "seatsWon: " << parties[i].getSeatsWon() << std::endl;
    std::cout << "remainder: " << parties[i].getRemainder() << std::endl;
  }
}

void OPL::displayResults() {
  std::cout << "General Election Information" << std::endl;
  printf("\tElection Type: OPL\n");
  printf("\tTotal Ballots: %d\n", numBallots);
  writeToMediaFile("Election Type: OPL\n");
  writeToMediaFile("Total Ballots: " + std::to_string(numBallots));
  std::cout << "\nWinners" << std::endl;
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  writeToMediaFile("Winners:\n");
  writeToAuditFile("Winners:\n");
  for (int i = 0; i < winners.size(); i++) {
    writeToAuditFile("Name: " + winners[i].getName() +
                     " Party: " + std::string(1, winners[i].getParty()) +
                     " Votes: " + std::to_string(winners[i].getNumBallots()) +
                     "\n");
    writeToMediaFile("Name: " + winners[i].getName() +
                     " Party: " + std::string(1, winners[i].getParty()) +
                     " Votes: " + std::to_string(winners[i].getNumBallots()) +
                     "\n");
    printf("\t%-60s %-15c %-d\n", winners[i].getName().c_str(),
           winners[i].getParty(), winners[i].getNumBallots());
  }

  std::cout << "\nLosers\n" << std::endl;
  printf("\t%-60s %-15s %-s", "Name", "Party", "Number of Ballots\n");
  writeToMediaFile("Losers:\n");
  for (int i = 0; i < losers.size(); i++) {
    writeToMediaFile("Name: " + losers[i].getName() +
                     " Party: " + std::string(1, losers[i].getParty()) +
                     " Votes: " + std::to_string(losers[i].getNumBallots()) +
                     "\n");
    printf("\t%-60s %-15c %-d\n", losers[i].getName().c_str(),
           losers[i].getParty(), losers[i].getNumBallots());
  }
}

void OPL::setParties(std::vector<Party> parties_) { parties = parties_; }
