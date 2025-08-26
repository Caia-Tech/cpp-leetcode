#include <gtest/gtest.h>
#include "../../src/easy/combine_two_tables.h"
#include <algorithm>

using namespace leetcode::easy;

// Test fixture for Combine Two Tables
class CombineTwoTablesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test data
        persons = {
            Person(1, "Wang", "Allen"),
            Person(2, "Alice", "Bob"),
            Person(3, "John", "Doe"),
            Person(4, "Jane", "Smith")
        };
        
        addresses = {
            Address(1, 2, "New York City", "New York"),
            Address(2, 3, "Leetcode", "California"),
            // Note: No address for person 1 and 4 - testing LEFT JOIN behavior
        };
        
        expected = {
            PersonAddress("Wang", "Allen", "", ""),           // Person 1: no address
            PersonAddress("Alice", "Bob", "New York City", "New York"),  // Person 2: has address
            PersonAddress("John", "Doe", "Leetcode", "California"),      // Person 3: has address  
            PersonAddress("Jane", "Smith", "", "")            // Person 4: no address
        };
    }
    
    std::vector<Person> persons;
    std::vector<Address> addresses;
    std::vector<PersonAddress> expected;
    
    void verifyResults(const std::vector<PersonAddress>& result, const std::vector<PersonAddress>& expected) {
        ASSERT_EQ(result.size(), expected.size()) << "Result size mismatch";
        
        for (size_t i = 0; i < result.size(); ++i) {
            EXPECT_EQ(result[i].firstName, expected[i].firstName) << "First name mismatch at index " << i;
            EXPECT_EQ(result[i].lastName, expected[i].lastName) << "Last name mismatch at index " << i;
            EXPECT_EQ(result[i].city, expected[i].city) << "City mismatch at index " << i;
            EXPECT_EQ(result[i].state, expected[i].state) << "State mismatch at index " << i;
        }
    }
};

// Test Case 1: Basic LEFT JOIN functionality
TEST_F(CombineTwoTablesTest, BasicLeftJoin) {
    auto result = CombineTwoTables::hashMapJoin(persons, addresses);
    verifyResults(result, expected);
}

// Test Case 2: All approaches should give same result
TEST_F(CombineTwoTablesTest, AllApproachesConsistent) {
    auto hashResult = CombineTwoTables::hashMapJoin(persons, addresses);
    auto nestedResult = CombineTwoTables::nestedLoopJoin(persons, addresses);
    auto mergeResult = CombineTwoTables::sortMergeJoin(persons, addresses);
    auto optimizedResult = CombineTwoTables::optimizedHashJoin(persons, addresses);
    
    verifyResults(hashResult, expected);
    verifyResults(nestedResult, expected);
    verifyResults(mergeResult, expected);
    verifyResults(optimizedResult, expected);
}

// Test Case 3: Empty tables
TEST_F(CombineTwoTablesTest, EmptyTables) {
    std::vector<Person> emptyPersons;
    std::vector<Address> emptyAddresses;
    
    auto result = CombineTwoTables::hashMapJoin(emptyPersons, addresses);
    EXPECT_TRUE(result.empty()) << "Empty persons should yield empty result";
    
    result = CombineTwoTables::hashMapJoin(persons, emptyAddresses);
    EXPECT_EQ(result.size(), persons.size()) << "All persons should be included with empty addresses";
    
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i].firstName, persons[i].firstName);
        EXPECT_EQ(result[i].lastName, persons[i].lastName);
        EXPECT_EQ(result[i].city, "");
        EXPECT_EQ(result[i].state, "");
    }
}

// Test Case 4: All persons have addresses
TEST_F(CombineTwoTablesTest, AllPersonsHaveAddresses) {
    std::vector<Person> testPersons = {
        Person(1, "John", "Doe"),
        Person(2, "Jane", "Smith")
    };
    
    std::vector<Address> testAddresses = {
        Address(1, 1, "New York", "NY"),
        Address(2, 2, "Los Angeles", "CA")
    };
    
    std::vector<PersonAddress> testExpected = {
        PersonAddress("John", "Doe", "New York", "NY"),
        PersonAddress("Jane", "Smith", "Los Angeles", "CA")
    };
    
    auto result = CombineTwoTables::hashMapJoin(testPersons, testAddresses);
    verifyResults(result, testExpected);
}

// Test Case 5: No persons have addresses
TEST_F(CombineTwoTablesTest, NoPersonsHaveAddresses) {
    std::vector<Person> testPersons = {
        Person(1, "John", "Doe"),
        Person(2, "Jane", "Smith")
    };
    
    std::vector<Address> testAddresses = {
        Address(1, 99, "New York", "NY"),    // personId 99 doesn't exist
        Address(2, 88, "Los Angeles", "CA")  // personId 88 doesn't exist
    };
    
    std::vector<PersonAddress> testExpected = {
        PersonAddress("John", "Doe", "", ""),
        PersonAddress("Jane", "Smith", "", "")
    };
    
    auto result = CombineTwoTables::hashMapJoin(testPersons, testAddresses);
    verifyResults(result, testExpected);
}

// Test Case 6: Single person, single address
TEST_F(CombineTwoTablesTest, SinglePersonSingleAddress) {
    std::vector<Person> testPersons = {Person(1, "Alice", "Wonder")};
    std::vector<Address> testAddresses = {Address(1, 1, "Wonderland", "Fantasy")};
    std::vector<PersonAddress> testExpected = {PersonAddress("Alice", "Wonder", "Wonderland", "Fantasy")};
    
    auto result = CombineTwoTables::hashMapJoin(testPersons, testAddresses);
    verifyResults(result, testExpected);
}

// Test Case 7: Multiple addresses per person (should take first one found)
TEST_F(CombineTwoTablesTest, MultipleAddressesPerPerson) {
    std::vector<Person> testPersons = {Person(1, "John", "Doe")};
    std::vector<Address> testAddresses = {
        Address(1, 1, "New York", "NY"),
        Address(2, 1, "Los Angeles", "CA")  // Same personId
    };
    
    auto result = CombineTwoTables::hashMapJoin(testPersons, testAddresses);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].firstName, "John");
    EXPECT_EQ(result[0].lastName, "Doe");
    // Should have some address (implementation dependent which one)
    EXPECT_FALSE(result[0].city.empty());
    EXPECT_FALSE(result[0].state.empty());
}

// Test Case 8: Large dataset performance test
TEST_F(CombineTwoTablesTest, LargeDataset) {
    std::vector<Person> largePersons;
    std::vector<Address> largeAddresses;
    
    // Create 1000 persons
    for (int i = 1; i <= 1000; ++i) {
        largePersons.emplace_back(i, "First" + std::to_string(i), "Last" + std::to_string(i));
    }
    
    // Create addresses for every other person (500 addresses)
    for (int i = 1; i <= 1000; i += 2) {
        largeAddresses.emplace_back(i, i, "City" + std::to_string(i), "State" + std::to_string(i));
    }
    
    auto result = CombineTwoTables::hashMapJoin(largePersons, largeAddresses);
    EXPECT_EQ(result.size(), 1000);
    
    // Verify that half have addresses and half don't
    int withAddress = 0, withoutAddress = 0;
    for (const auto& person : result) {
        if (person.city.empty()) {
            withoutAddress++;
        } else {
            withAddress++;
        }
    }
    
    EXPECT_EQ(withAddress, 500);
    EXPECT_EQ(withoutAddress, 500);
}

// Test Case 9: SQL query string verification
TEST_F(CombineTwoTablesTest, SQLQueryVerification) {
    std::string sql = CombineTwoTables::getSQLLeftJoin();
    
    // Verify that SQL contains necessary keywords
    std::transform(sql.begin(), sql.end(), sql.begin(), ::toupper);
    EXPECT_NE(sql.find("SELECT"), std::string::npos) << "SQL should contain SELECT";
    EXPECT_NE(sql.find("FROM"), std::string::npos) << "SQL should contain FROM";
    EXPECT_NE(sql.find("LEFT JOIN"), std::string::npos) << "SQL should contain LEFT JOIN";
    EXPECT_NE(sql.find("ON"), std::string::npos) << "SQL should contain ON";
    EXPECT_NE(sql.find("PERSONID"), std::string::npos) << "SQL should reference personId";
}

// Test Case 10: SQL variants verification
TEST_F(CombineTwoTablesTest, SQLVariantsVerification) {
    auto variants = CombineTwoTables::getSQLVariants();
    
    EXPECT_GE(variants.size(), 3) << "Should have at least 3 SQL variants";
    
    for (const auto& variant : variants) {
        EXPECT_FALSE(variant.empty()) << "SQL variant should not be empty";
        // Each variant should be a valid SQL-like string
        std::string upperVariant = variant;
        std::transform(upperVariant.begin(), upperVariant.end(), upperVariant.begin(), ::toupper);
        EXPECT_NE(upperVariant.find("SELECT"), std::string::npos) << "Each variant should contain SELECT";
    }
}

// Test Case 11: Edge case - persons with special characters in names
TEST_F(CombineTwoTablesTest, SpecialCharactersInNames) {
    std::vector<Person> testPersons = {
        Person(1, "Jean-Luc", "O'Connor"),
        Person(2, "María", "González-Smith"),
        Person(3, "", "")  // Empty names
    };
    
    std::vector<Address> testAddresses = {
        Address(1, 1, "Saint-Jean", "Québec")
    };
    
    auto result = CombineTwoTables::hashMapJoin(testPersons, testAddresses);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].firstName, "Jean-Luc");
    EXPECT_EQ(result[0].lastName, "O'Connor");
    EXPECT_EQ(result[0].city, "Saint-Jean");
    EXPECT_EQ(result[0].state, "Québec");
    
    EXPECT_EQ(result[1].firstName, "María");
    EXPECT_EQ(result[1].city, "");  // No address
    
    EXPECT_EQ(result[2].firstName, "");
    EXPECT_EQ(result[2].lastName, "");
}

// Test Case 12: Performance comparison between approaches
TEST_F(CombineTwoTablesTest, PerformanceComparison) {
    // Create medium-sized dataset
    std::vector<Person> mediumPersons;
    std::vector<Address> mediumAddresses;
    
    for (int i = 1; i <= 100; ++i) {
        mediumPersons.emplace_back(i, "First" + std::to_string(i), "Last" + std::to_string(i));
    }
    
    for (int i = 1; i <= 50; ++i) {  // Half have addresses
        mediumAddresses.emplace_back(i, i, "City" + std::to_string(i), "State" + std::to_string(i));
    }
    
    // All approaches should give the same result
    auto hashResult = CombineTwoTables::hashMapJoin(mediumPersons, mediumAddresses);
    auto nestedResult = CombineTwoTables::nestedLoopJoin(mediumPersons, mediumAddresses);
    auto mergeResult = CombineTwoTables::sortMergeJoin(mediumPersons, mediumAddresses);
    auto optimizedResult = CombineTwoTables::optimizedHashJoin(mediumPersons, mediumAddresses);
    
    // Results should be identical (though order might differ for some approaches)
    EXPECT_EQ(hashResult.size(), nestedResult.size());
    EXPECT_EQ(hashResult.size(), mergeResult.size());
    EXPECT_EQ(hashResult.size(), optimizedResult.size());
    EXPECT_EQ(hashResult.size(), 100);  // All persons included
}

// Test Case 13: Stress test with edge cases
TEST_F(CombineTwoTablesTest, StressTestEdgeCases) {
    // Test with maximum and minimum person IDs
    std::vector<Person> stressPersons = {
        Person(1, "Min", "Person"),
        Person(2147483647, "Max", "Person"),  // Maximum int value
        Person(0, "Zero", "Person")           // Edge case
    };
    
    std::vector<Address> stressAddresses = {
        Address(1, 1, "Min City", "Min State"),
        Address(2, 2147483647, "Max City", "Max State")
        // No address for person 0
    };
    
    auto result = CombineTwoTables::hashMapJoin(stressPersons, stressAddresses);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].city, "Min City");      // Person 1 has address
    EXPECT_EQ(result[1].city, "Max City");      // Person 2147483647 has address
    EXPECT_EQ(result[2].city, "");              // Person 0 has no address
}

