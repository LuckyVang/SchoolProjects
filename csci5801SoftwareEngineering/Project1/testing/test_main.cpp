#include "BallotUnitTest.cpp"
#include "CandidateTest.cpp"
#include "HelperTest.cpp"
#include "IRTest.cpp"
#include "OPLTest.cpp"
#include "PartyTest.cpp"

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}