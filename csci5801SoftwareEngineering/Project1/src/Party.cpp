#include "../src/Party.h"

Party::Party(char p) : name(p) {}

char Party::getPartyName() { return name; }

int Party::getNumBallots() {
  int total = 0;
  for (auto it = partyMembers.begin(); it != partyMembers.end(); it++) {
    total += (*it)->getNumBallots();
  }
  return total;
}

void Party::sortByVotes() {
  int i, j;
  for (i = 1; i < partyMembers.size(); i++) {
    Candidate* key = partyMembers[i];
    j = i - 1;
    while (j >= 0 && partyMembers[j]->getNumBallots() < key->getNumBallots()) {
      partyMembers[j + 1] = partyMembers[j];
      j = j - 1;
    }
    partyMembers[j + 1] = key;
  }
}

int Party::getSeatsWon() { return seatsWon; }

int Party::getRemainder() { return remainder; }

std::vector<Candidate *> Party::getPartyMembers() { return partyMembers; }

void Party::setNumBallots(int num) { numBallots = num; }

void Party::setSeatsWon(int seats) { seatsWon = seats; }

void Party::setRemainder(int num) { remainder = num; }

void Party::addCandidate(Candidate *candidate) {
  partyMembers.push_back(candidate);
}

bool Party::operator==(Party& r) {
    return getPartyName() == r.getPartyName();
}