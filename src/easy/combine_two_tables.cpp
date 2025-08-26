#include "combine_two_tables.h"
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace easy {

// Approach 1: SQL Left Join (Standard)
// Detailed Reasoning: LEFT JOIN is the perfect SQL operation for this problem.
// It returns all records from the left table (Person) and matching records from
// the right table (Address). If no match exists, NULL values are returned for
// the right table columns. This ensures we get all persons even without addresses.
std::string CombineTwoTables::getSQLLeftJoin() {
    return R"(
        SELECT 
            p.firstName, 
            p.lastName, 
            a.city, 
            a.state
        FROM Person p
        LEFT JOIN Address a ON p.personId = a.personId;
    )";
}

// Approach 2: Hash Map Join (C++ Implementation)
// Detailed Reasoning: Build a hash map from personId to Address for O(1) lookups.
// Then iterate through all persons and look up their addresses. This mimics the
// efficiency of a database hash join and is optimal for this type of operation.
std::vector<PersonAddress> CombineTwoTables::hashMapJoin(
    const std::vector<Person>& persons,
    const std::vector<Address>& addresses) {
    
    std::vector<PersonAddress> result;
    
    // Build hash map: personId -> Address
    std::unordered_map<int, Address> addressMap;
    for (const auto& addr : addresses) {
        addressMap[addr.personId] = addr;
    }
    
    // Join with Person table
    for (const auto& person : persons) {
        auto it = addressMap.find(person.personId);
        if (it != addressMap.end()) {
            // Found matching address
            result.emplace_back(person.firstName, person.lastName, 
                              it->second.city, it->second.state);
        } else {
            // No address found, use empty strings (equivalent to NULL)
            result.emplace_back(person.firstName, person.lastName);
        }
    }
    
    return result;
}

// Approach 3: Nested Loop Join
// Detailed Reasoning: For each person, scan all addresses to find a match.
// This is inefficient O(n*m) but works well for small datasets and is easy
// to understand. It's equivalent to the basic nested loop join in databases.
std::vector<PersonAddress> CombineTwoTables::nestedLoopJoin(
    const std::vector<Person>& persons,
    const std::vector<Address>& addresses) {
    
    std::vector<PersonAddress> result;
    
    for (const auto& person : persons) {
        bool found = false;
        
        // Search for matching address
        for (const auto& addr : addresses) {
            if (addr.personId == person.personId) {
                result.emplace_back(person.firstName, person.lastName, 
                                  addr.city, addr.state);
                found = true;
                break; // Assuming one address per person
            }
        }
        
        // If no address found, add person with empty address fields
        if (!found) {
            result.emplace_back(person.firstName, person.lastName);
        }
    }
    
    return result;
}

// Approach 4: Sort-Merge Join
// Detailed Reasoning: Sort both tables by personId, then merge them in linear time.
// This is efficient when data is already sorted or when we need to join large datasets.
// It's a classic algorithm used in database systems for joining sorted relations.
std::vector<PersonAddress> CombineTwoTables::sortMergeJoin(
    std::vector<Person> persons,
    std::vector<Address> addresses) {
    
    std::vector<PersonAddress> result;
    
    // Sort both vectors by personId
    std::sort(persons.begin(), persons.end(), comparePersonById);
    std::sort(addresses.begin(), addresses.end(), compareAddressByPersonId);
    
    // Merge the sorted lists
    size_t personIdx = 0, addressIdx = 0;
    
    while (personIdx < persons.size()) {
        const auto& person = persons[personIdx];
        
        // Find matching address(es)
        bool found = false;
        while (addressIdx < addresses.size() && 
               addresses[addressIdx].personId < person.personId) {
            addressIdx++;
        }
        
        if (addressIdx < addresses.size() && 
            addresses[addressIdx].personId == person.personId) {
            // Found matching address
            result.emplace_back(person.firstName, person.lastName,
                              addresses[addressIdx].city, addresses[addressIdx].state);
            found = true;
        }
        
        if (!found) {
            // No address found
            result.emplace_back(person.firstName, person.lastName);
        }
        
        personIdx++;
    }
    
    return result;
}

// Approach 5: Hash Join with Optimization
// Detailed Reasoning: Build hash table on the smaller relation to minimize memory usage.
// This optimization is commonly used in database systems. If addresses are fewer than
// persons, build the hash table on addresses; otherwise, build it on persons.
std::vector<PersonAddress> CombineTwoTables::optimizedHashJoin(
    const std::vector<Person>& persons,
    const std::vector<Address>& addresses) {
    
    std::vector<PersonAddress> result;
    
    if (addresses.size() <= persons.size()) {
        // Build hash table on smaller table (addresses)
        return hashMapJoin(persons, addresses);
    } else {
        // Build hash table on persons (less common case)
        std::unordered_map<int, Person> personMap;
        for (const auto& person : persons) {
            personMap[person.personId] = person;
        }
        
        // Track which persons we've seen
        std::unordered_set<int> seenPersons;
        
        // Process addresses and join with persons
        for (const auto& addr : addresses) {
            auto it = personMap.find(addr.personId);
            if (it != personMap.end()) {
                result.emplace_back(it->second.firstName, it->second.lastName,
                                  addr.city, addr.state);
                seenPersons.insert(addr.personId);
            }
        }
        
        // Add persons without addresses
        for (const auto& person : persons) {
            if (seenPersons.find(person.personId) == seenPersons.end()) {
                result.emplace_back(person.firstName, person.lastName);
            }
        }
    }
    
    return result;
}

// Approach 6: SQL Variants
// Detailed Reasoning: There are multiple ways to write the same query in SQL.
// Each has subtle differences in readability and potentially performance,
// but they all achieve the same logical result.
std::vector<std::string> CombineTwoTables::getSQLVariants() {
    return {
        // Standard LEFT JOIN
        R"(SELECT p.firstName, p.lastName, a.city, a.state
           FROM Person p LEFT JOIN Address a ON p.personId = a.personId;)",
        
        // LEFT OUTER JOIN (explicit)
        R"(SELECT p.firstName, p.lastName, a.city, a.state
           FROM Person p LEFT OUTER JOIN Address a ON p.personId = a.personId;)",
        
        // Using table aliases for clarity
        R"(SELECT Person.firstName, Person.lastName, Address.city, Address.state
           FROM Person LEFT JOIN Address ON Person.personId = Address.personId;)",
        
        // Using WHERE clause (less common but equivalent)
        R"(SELECT p.firstName, p.lastName, a.city, a.state
           FROM Person p, Address a WHERE p.personId = a.personId(+);)",
        
        // Subquery approach (less efficient but educational)
        R"(SELECT firstName, lastName,
               (SELECT city FROM Address WHERE personId = Person.personId) as city,
               (SELECT state FROM Address WHERE personId = Person.personId) as state
           FROM Person;)",
        
        // Common Table Expression approach
        R"(WITH PersonAddress AS (
               SELECT p.personId, p.firstName, p.lastName, a.city, a.state
               FROM Person p LEFT JOIN Address a ON p.personId = a.personId
           )
           SELECT firstName, lastName, city, state FROM PersonAddress;)"
    };
}

// Helper function implementations
bool CombineTwoTables::comparePersonById(const Person& a, const Person& b) {
    return a.personId < b.personId;
}

bool CombineTwoTables::compareAddressByPersonId(const Address& a, const Address& b) {
    return a.personId < b.personId;
}

std::unordered_map<int, Address> CombineTwoTables::buildAddressMap(const std::vector<Address>& addresses) {
    std::unordered_map<int, Address> map;
    for (const auto& addr : addresses) {
        map[addr.personId] = addr;
    }
    return map;
}

const Address* CombineTwoTables::findAddressForPerson(const std::vector<Address>& sortedAddresses, int personId) {
    auto it = std::lower_bound(sortedAddresses.begin(), sortedAddresses.end(), 
                              Address(0, personId, "", ""), compareAddressByPersonId);
    
    if (it != sortedAddresses.end() && it->personId == personId) {
        return &(*it);
    }
    
    return nullptr;
}

} // namespace easy
} // namespace leetcode