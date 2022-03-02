#include "gtest/gtest.h"

class PartyTest : public ::testing::Test {
 public:
  PartyTest() {
    // initialization code here
  }

  void SetUp() {
    D = new Party('D');
    Derrick = new Candidate('D', "Derrick");
    Derrick2 = new Candidate('D', "Derrick2");

    std::vector<int> i1{1, 0, 0};
    Ballot b1(i1);
    for (int i = 0; i < 6; i++) {
      Derrick->addBallot(b1);
    }
    for (int i = 0; i < 4; i++) {
      Derrick2->addBallot(b1);
    }

    D->setSeatsWon(2);
    D->setRemainder(1);

    D->addCandidate(Derrick);
    D->addCandidate(Derrick2);
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to throw exceptions from here if need be
  }

  ~PartyTest() {
    // cleanup any pending stuff, but no exceptions allowed
  }

  Party *D;
  Party *R;
  Party *I;
  Party *L;

  Candidate *Derrick;
  Candidate *Derrick2;
};

TEST_F(PartyTest, getPartyName1) {
  EXPECT_EQ('D', D->getPartyName()) << "getPartyName1: party name is incorrect";
}
TEST_F(PartyTest, getNumBallots1) {
  EXPECT_EQ(10, D->getNumBallots())
      << "getNumBallots1: number of ballots is incorrect";
}
TEST_F(PartyTest, getSeatsWon1) {
  EXPECT_EQ(2, D->getSeatsWon())
      << "getSeatsWon1: number of seats won is incorrect";
}
TEST_F(PartyTest, getRemainder1) {
  EXPECT_EQ(1, D->getRemainder()) << "getRemainder1: remainder is incorrect";
}
TEST_F(PartyTest, getPartyMembers1) {
  std::vector<Candidate *> candidates{Derrick, Derrick2};
  std::vector<Candidate *> partyMembers = D->getPartyMembers();
  for (int i = 0; i < candidates.size(); i++) {
    EXPECT_EQ(partyMembers.at(i), candidates.at(i))
        << "getPartyMembers1: party vector is incorrect";
  }
}
// already sorted
TEST_F(PartyTest, sortByVotes1) {
  Candidate *Derrick3 = new Candidate('D', "Derrick3");
  std::vector<int> i1{1, 0, 0};
  Ballot b1(i1);
  for (int i = 0; i < 2; i++) {
    Derrick3->addBallot(b1);
  }
  D->addCandidate(Derrick3);
  D->sortByVotes();
  std::vector<Candidate *> candidates = D->getPartyMembers();
  for (int i = 0; i < candidates.size() - 1; i++) {
    EXPECT_TRUE(candidates.at(i)->getNumBallots() >=
                candidates.at(i + 1)->getNumBallots())
        << "sortByVotes1: candidates vector isn't sorted correctly";
  }
}
// already in reverse sorted order
TEST_F(PartyTest, sortByVotesPreReverseOrder1) {
  Party D2('D');
  Candidate *Derrick3 = new Candidate('D', "Derrick3");
  std::vector<int> i1{1, 0, 0};
  Ballot b1(i1);
  for (int i = 0; i < 2; i++) {
    Derrick3->addBallot(b1);
  }

  D2.addCandidate(Derrick3);
  D2.addCandidate(Derrick2);
  D2.addCandidate(Derrick);

  D2.sortByVotes();

  std::vector<Candidate *> candidates = D2.getPartyMembers();

  for (int i = 0; i < candidates.size() - 1; i++) {
    EXPECT_TRUE(candidates.at(i)->getNumBallots() >=
                candidates.at(i + 1)->getNumBallots())
        << "sortByVotesPreReverseOrder1: candidates vector isn't sortd "
           "correctly";
  }
}
TEST_F(PartyTest, setNumBallots1) {
  D->setNumBallots(10);
  EXPECT_EQ(10, D->getVariableNumBallots())<<"setNumBallots1: set the number of ballots incorrectly";
}
TEST_F(PartyTest, setSeatsWon1) {
  D->setSeatsWon(5);
  EXPECT_EQ(5, D->getSeatsWon())<<"setSeatsWon1: set the number of seats won incorrectly";
}
TEST_F(PartyTest, setRemainder1) {
  D->setRemainder(5);
  EXPECT_EQ(5, D->getRemainder())<<"setRemainder1: set the remainder incorrectly";
}
TEST_F(PartyTest, addCandidate1) {
  Candidate *Derrick3 = new Candidate('D', "Derrick3");
  D->addCandidate(Derrick3);
  EXPECT_EQ(Derrick3, D->getPartyMembers().at(2))<<"addCandidate1: failed to add a candidate to a Party";
}