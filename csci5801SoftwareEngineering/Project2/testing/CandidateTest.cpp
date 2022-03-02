#include <vector>

#include "../src/Candidate.cpp"
#include "../src/Party.cpp"
#include "gtest/gtest.h"

class CandidateTests : public ::testing::Test {
 public:
  void SetUp() {}
};

TEST_F(CandidateTests, getNameTest) {
  Candidate Bob = Candidate('I', "Bob");
  Candidate Jane = Candidate('D', "Jane");
  Candidate David = Candidate('L', "Dave");
  EXPECT_EQ(Bob.getName(), "Bob") << "GetParty has errors";
  EXPECT_EQ(Jane.getName(), "Jane") << "GetParty has errors";
  EXPECT_EQ(David.getName(), "Dave") << "GetParty has errors";
}

TEST_F(CandidateTests, getPartyTest) {
  Candidate Bob = Candidate('I', "Bob");
  Candidate Jane = Candidate('2', "Jane");
  Candidate David = Candidate('*', "Dave");
  Candidate Space = Candidate(' ', "Space");
  EXPECT_EQ(Bob.getParty(), 'I') << "GetParty has errors";
  EXPECT_EQ(Jane.getParty(), '2') << "GetParty has errors";
  EXPECT_EQ(David.getParty(), '*') << "GetParty has errors";
  EXPECT_EQ(Space.getParty(), ' ') << "GetParty has errors";
}

TEST_F(CandidateTests, getNumBallotsTest) {
  Candidate Bob = Candidate('I', "Bob");
  Candidate Jane = Candidate('D', "Jane");
  Candidate David = Candidate('L', "Dave");
  Ballot ballot1({1, 2, 3});
  David.addBallot(ballot1);
  for (int i = 0; i < 100000; i++) {
    Jane.addBallot(ballot1);
  }
  EXPECT_EQ(Bob.getNumBallots(), 0) << "GetBallots has errors";
  EXPECT_EQ(Jane.getNumBallots(), 100000) << "GetBallots has errors";
  EXPECT_EQ(David.getNumBallots(), 1) << "GetBallots has errors";
}

TEST_F(CandidateTests, getInitBallotsTest) {
  Candidate Bob = Candidate('I', "Bob");
  Candidate Jane = Candidate('D', "Jane");
  Candidate David = Candidate('L', "Dave");
  Bob.setInitBallots(100);
  Jane.setInitBallots(-10);
  David.setInitBallots(0);
  EXPECT_EQ(Bob.getInitBallots(), 100) << "GetBallots has errors";
  EXPECT_EQ(Jane.getInitBallots(), -10) << "GetBallots has errors";
  EXPECT_EQ(David.getInitBallots(), 0) << "GetBallots has errors";
}

TEST_F(CandidateTests, getBallotsTest) {
  Candidate Bob = Candidate('I', "Bob");
  Candidate Jane = Candidate('D', "Jane");
  Candidate David = Candidate('L', "Dave");
  std::vector<Candidate> candidates;
  std::vector<int> ballotCandidates;
  std::vector<int> ballotCandidates2;
  std::vector<int> ballotCandidates3;

  candidates.push_back(Bob);
  candidates.push_back(Jane);
  candidates.push_back(David);

  ballotCandidates.push_back(2);
  ballotCandidates.push_back(3);
  ballotCandidates.push_back(1);

  ballotCandidates2.push_back(1);
  ballotCandidates2.push_back(2);
  ballotCandidates2.push_back(3);

  ballotCandidates3.push_back(3);
  ballotCandidates3.push_back(2);
  ballotCandidates3.push_back(1);

  Ballot ballot1(ballotCandidates);
  Ballot ballot2(ballotCandidates2);
  Ballot ballot3(ballotCandidates3);

  Bob.addBallot(ballot1);
  Bob.addBallot(ballot2);
  Bob.addBallot(ballot3);

  std::vector<Ballot> ballotVec;
  ballotVec.push_back(ballot1);
  ballotVec.push_back(ballot2);
  ballotVec.push_back(ballot3);

  EXPECT_EQ(Bob.getBallots().at(0).getCandidates(),
            ballotVec.at(0).getCandidates())
      << "GetBallots has errors";
  EXPECT_EQ(Bob.getBallots().at(1).getCandidates(),
            ballotVec.at(1).getCandidates())
      << "GetBallots has errors";

  EXPECT_EQ(Bob.getBallots().at(2).getCandidates(),
            ballotVec.at(2).getCandidates())
      << "GetBallots has errors";
}