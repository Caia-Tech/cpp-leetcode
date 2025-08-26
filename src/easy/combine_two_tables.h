#pragma once

#ifndef LEETCODE_EASY_COMBINE_TWO_TABLES_H
#define LEETCODE_EASY_COMBINE_TWO_TABLES_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace leetcode {
namespace easy {

// Problem 175: Combine Two Tables
// This is a database problem that demonstrates SQL JOIN operations.
// 
// Table: Person
// +-------------+---------+
// | Column Name | Type    |
// +-------------+---------+
// | personId    | int     |
// | lastName    | varchar |
// | firstName   | varchar |
// +-------------+---------+
// personId is the primary key column for this table.
// This table contains information about the ID of some persons and their first and last names.
//
// Table: Address
// +-------------+---------+
// | Column Name | Type    |
// +-------------+---------+
// | addressId   | int     |
// | personId    | int     |
// | city        | varchar |
// | state       | varchar |
// +-------------+---------+
// addressId is the primary key column for this table.
// Each row of this table contains information about the city and state of one person with ID = PersonId.
//
// Write an SQL query to report the first name, last name, city, and state of each person in the Person table.
// If the address of a personId is not present in the Address table, report null instead.
//
// Since this is a SQL problem, we'll implement different JOIN approaches and provide
// equivalent C++ implementations for educational purposes.

struct Person {
    int personId;
    std::string firstName;
    std::string lastName;
    
    Person() : personId(0) {}
    Person(int id, const std::string& first, const std::string& last)
        : personId(id), firstName(first), lastName(last) {}
};

struct Address {
    int addressId;
    int personId;
    std::string city;
    std::string state;
    
    Address() : addressId(0), personId(0) {}
    Address(int addrId, int pId, const std::string& c, const std::string& s)
        : addressId(addrId), personId(pId), city(c), state(s) {}
};

struct PersonAddress {
    std::string firstName;
    std::string lastName;
    std::string city;     // Can be empty if no address found
    std::string state;    // Can be empty if no address found
    
    PersonAddress(const std::string& first, const std::string& last, 
                  const std::string& c = "", const std::string& s = "")
        : firstName(first), lastName(last), city(c), state(s) {}
};

// This class demonstrates 6 different approaches to solving the JOIN problem:
// 1. SQL Left Join (Standard): The most common SQL approach
// 2. Hash Map Join: C++ implementation using hash maps
// 3. Nested Loop Join: Brute force approach for small datasets
// 4. Sort-Merge Join: Efficient join for sorted data
// 5. Hash Join with Optimization: Optimized hash-based join
// 6. SQL Variants: Different SQL formulations of the same query

class CombineTwoTables {
public:
    // Approach 1: SQL Left Join (returns the SQL query string)
    // Time: O(n + m), Space: O(1) for query, O(n + m) for execution
    // This is the standard SQL approach using LEFT JOIN
    static std::string getSQLLeftJoin();
    
    // Approach 2: Hash Map Join (C++ Implementation)
    // Time: O(n + m), Space: O(m) for hash map
    // Build hash map from Address table, then join with Person table
    static std::vector<PersonAddress> hashMapJoin(
        const std::vector<Person>& persons,
        const std::vector<Address>& addresses
    );
    
    // Approach 3: Nested Loop Join
    // Time: O(n * m), Space: O(1)
    // For each person, scan all addresses to find matching personId
    static std::vector<PersonAddress> nestedLoopJoin(
        const std::vector<Person>& persons,
        const std::vector<Address>& addresses
    );
    
    // Approach 4: Sort-Merge Join
    // Time: O(n log n + m log m), Space: O(1)
    // Sort both tables by personId, then merge them efficiently
    static std::vector<PersonAddress> sortMergeJoin(
        std::vector<Person> persons,  // Pass by value to allow sorting
        std::vector<Address> addresses // Pass by value to allow sorting
    );
    
    // Approach 5: Hash Join with Optimization
    // Time: O(n + m), Space: O(min(n, m))
    // Build hash table on smaller table for better memory usage
    static std::vector<PersonAddress> optimizedHashJoin(
        const std::vector<Person>& persons,
        const std::vector<Address>& addresses
    );
    
    // Approach 6: SQL Variants (different SQL formulations)
    // Returns multiple equivalent SQL queries
    static std::vector<std::string> getSQLVariants();

private:
    // Helper function to compare persons by ID for sorting
    static bool comparePersonById(const Person& a, const Person& b);
    
    // Helper function to compare addresses by person ID for sorting
    static bool compareAddressByPersonId(const Address& a, const Address& b);
    
    // Helper function to build address lookup map
    static std::unordered_map<int, Address> buildAddressMap(const std::vector<Address>& addresses);
    
    // Helper function for binary search in sorted addresses
    static const Address* findAddressForPerson(const std::vector<Address>& sortedAddresses, int personId);
};

} // namespace easy
} // namespace leetcode

#endif // LEETCODE_EASY_COMBINE_TWO_TABLES_H