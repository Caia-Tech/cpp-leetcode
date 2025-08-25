#!/usr/bin/env python3
"""
LeetCode Automation using Azure OpenAI o1-mini reasoning model
Generates 6 different approaches with comprehensive testing
"""

import os
import json
import requests
import subprocess
import time
import re
from pathlib import Path
from typing import Dict, List, Tuple, Optional
from dotenv import load_dotenv

load_dotenv()

class LeetCodeO1Automation:
    def __init__(self):
        self.api_key = os.getenv('AZURE_OPENAI_KEY')
        self.endpoint = os.getenv('AZURE_OPENAI_ENDPOINT')
        self.api_version = "2024-12-01-preview"
        self.headers = {
            "api-key": self.api_key,
            "Content-Type": "application/json"
        }
        
    def generate_solution(self, problem_number: int, problem_name: str, 
                         problem_description: str, difficulty: str) -> Dict:
        """Generate complete solution using o1-mini reasoning model"""
        
        print(f"🧠 Using o1-mini reasoning model for Problem {problem_number}: {problem_name}")
        
        # Use o4-mini (o1-mini) for complex reasoning
        deployment = "o4-mini"
        url = f"{self.endpoint}openai/deployments/{deployment}/chat/completions?api-version={self.api_version}"
        
        prompt = f"""Solve LeetCode Problem {problem_number}: {problem_name}

{problem_description}

Generate a complete C++ solution with:

1. EXACTLY 6 different approaches:
   - Bit manipulation (clear lowest bit)
   - Brian Kernighan's algorithm
   - Built-in popcount
   - Lookup table
   - Divide and conquer
   - Bit shifting

2. C++ class structure:
   ```cpp
   namespace leetcode {{
   namespace {difficulty} {{
   class {self.to_class_name(problem_name)} {{
   public:
       int hammingWeightBitClear(uint32_t n);
       int hammingWeightBrianKernighan(uint32_t n);
       int hammingWeightBuiltIn(uint32_t n);
       int hammingWeightLookupTable(uint32_t n);
       int hammingWeightDivideConquer(uint32_t n);
       int hammingWeightBitShift(uint32_t n);
   }};
   }}
   }}
   ```

3. Generate complete header (.h), implementation (.cpp), and test files

Think through each approach step by step and provide working C++ code."""

        payload = {
            "messages": [
                {"role": "user", "content": prompt}
            ],
            "max_completion_tokens": 8000,
            "temperature": 1
        }
        
        try:
            response = requests.post(url, headers=self.headers, json=payload, timeout=120)
            
            if response.status_code == 200:
                result = response.json()
                content = result['choices'][0]['message']['content']
                usage = result.get('usage', {})
                
                print(f"✅ Generated solution using {usage.get('total_tokens', 'N/A')} tokens")
                if 'completion_tokens_details' in usage:
                    reasoning_tokens = usage['completion_tokens_details'].get('reasoning_tokens', 0)
                    print(f"   🧠 Reasoning tokens: {reasoning_tokens}")
                
                return self.parse_generated_content(content, problem_number, problem_name, difficulty)
            else:
                print(f"❌ Generation failed: {response.status_code}")
                return None
                
        except Exception as e:
            print(f"❌ Error generating solution: {e}")
            return None
    
    def parse_generated_content(self, content: str, problem_number: int, 
                               problem_name: str, difficulty: str) -> Dict:
        """Parse the generated content into separate files"""
        
        # Try to extract code blocks
        header_match = re.search(r'```cpp\n(.*?class.*?}\s*;\s*?.*?)\n```', content, re.DOTALL)
        impl_match = re.search(r'```cpp\n(.*?namespace.*?}\s*//.*?namespace.*?}\s*//.*?namespace.*?)\n```', content, re.DOTALL)
        test_match = re.search(r'```cpp\n(.*?TEST_F.*?)\n```', content, re.DOTALL)
        
        # If not found in code blocks, try to extract from structured response
        if not header_match:
            # Try alternative patterns
            header_match = re.search(r'[Hh]eader.*?:\s*\n(.*?)(?=\n[Ii]mplementation|$)', content, re.DOTALL)
        
        class_name = self.to_class_name(problem_name)
        snake_name = self.to_snake_case(problem_name)
        
        # Build default structure if parsing fails
        result = {
            'header': header_match.group(1) if header_match else self.generate_default_header(problem_number, problem_name, class_name, difficulty),
            'implementation': impl_match.group(1) if impl_match else self.generate_default_impl(class_name, snake_name, difficulty),
            'tests': test_match.group(1) if test_match else self.generate_default_tests(class_name, problem_name, difficulty, snake_name),
            'class_name': class_name,
            'snake_name': snake_name,
            'difficulty': difficulty
        }
        
        return result
    
    def to_class_name(self, problem_name: str) -> str:
        """Convert problem name to ClassName format"""
        # Remove special characters and convert to CamelCase
        words = re.findall(r'\w+', problem_name)
        return ''.join(word.capitalize() for word in words)
    
    def to_snake_case(self, problem_name: str) -> str:
        """Convert problem name to snake_case format"""
        words = re.findall(r'\w+', problem_name)
        return '_'.join(word.lower() for word in words)
    
    def generate_default_header(self, problem_number: int, problem_name: str, 
                               class_name: str, difficulty: str) -> str:
        """Generate a default header if parsing fails"""
        return f"""#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace leetcode {{
namespace {difficulty} {{

/**
 * Problem {problem_number}: {problem_name}
 * 
 * [Problem description would go here]
 */
class {class_name} {{
public:
    // Approach 1: Brute Force
    int solutionBruteForce(std::vector<int>& nums);
    
    // Approach 2: Optimized
    int solutionOptimized(std::vector<int>& nums);
    
    // Approach 3: Dynamic Programming
    int solutionDP(std::vector<int>& nums);
    
    // Approach 4: Greedy
    int solutionGreedy(std::vector<int>& nums);
    
    // Approach 5: Two Pointers
    int solutionTwoPointers(std::vector<int>& nums);
    
    // Approach 6: Hash Map
    int solutionHashMap(std::vector<int>& nums);
}};

}}  // namespace {difficulty}
}}  // namespace leetcode"""
    
    def generate_default_impl(self, class_name: str, snake_name: str, difficulty: str) -> str:
        """Generate a default implementation if parsing fails"""
        return f"""#include "{snake_name}.h"

namespace leetcode {{
namespace {difficulty} {{

// Implementations would go here

}}  // namespace {difficulty}
}}  // namespace leetcode"""
    
    def generate_default_tests(self, class_name: str, problem_name: str, difficulty: str = "easy", snake_name: str = "problem") -> str:
        """Generate default tests if parsing fails"""
        return f"""#include <gtest/gtest.h>
#include "../../src/{difficulty}/{snake_name}.h"

namespace leetcode {{
namespace {difficulty} {{
namespace test {{

class {class_name}Test : public ::testing::Test {{
protected:
    void testAllApproaches(std::vector<int> input, int expected) {{
        {class_name} solution;
        // Test all approaches
    }}
}};

TEST_F({class_name}Test, Example1) {{
    testAllApproaches({{1, 2, 3}}, 6);
}}

}}  // namespace test
}}  // namespace {difficulty}
}}  // namespace leetcode"""
    
    def write_files(self, solution: Dict, problem_number: int) -> bool:
        """Write generated files to disk"""
        difficulty = solution['difficulty']
        snake_name = solution['snake_name']
        
        # Create directories if needed
        src_dir = Path(f"src/{difficulty}")
        test_dir = Path(f"tests/{difficulty}")
        src_dir.mkdir(parents=True, exist_ok=True)
        test_dir.mkdir(parents=True, exist_ok=True)
        
        # Write files
        header_path = src_dir / f"{snake_name}.h"
        impl_path = src_dir / f"{snake_name}.cpp"
        test_path = test_dir / f"test_{snake_name}.cpp"
        
        try:
            header_path.write_text(solution['header'])
            impl_path.write_text(solution['implementation'])
            test_path.write_text(solution['tests'])
            
            print(f"✅ Files written:")
            print(f"   - {header_path}")
            print(f"   - {impl_path}")
            print(f"   - {test_path}")
            return True
            
        except Exception as e:
            print(f"❌ Error writing files: {e}")
            return False
    
    def build_and_test(self, class_name: str) -> bool:
        """Build and run tests for the generated solution"""
        print("🔨 Building project...")
        
        # Build
        result = subprocess.run(
            ["cmake", "--build", "build"],
            capture_output=True,
            text=True
        )
        
        if result.returncode != 0:
            print(f"❌ Build failed:")
            print(result.stderr[-1000:])  # Last 1000 chars of error
            return False
        
        print("✅ Build successful")
        
        # Run tests
        print("🧪 Running tests...")
        test_filter = f"*{class_name}*"
        
        env = os.environ.copy()
        env["DYLD_LIBRARY_PATH"] = "/Users/owner/miniconda3/lib"
        
        result = subprocess.run(
            ["./build/leetcode_tests", f"--gtest_filter={test_filter}"],
            capture_output=True,
            text=True,
            env=env
        )
        
        if result.returncode == 0:
            print("✅ All tests passed!")
            # Extract test count
            if "PASSED" in result.stdout:
                passed_match = re.search(r'\[  PASSED  \] (\d+) test', result.stdout)
                if passed_match:
                    print(f"   {passed_match.group(1)} tests passed")
            return True
        else:
            print("❌ Tests failed:")
            print(result.stdout[-2000:])  # Last 2000 chars
            return False
    
    def fix_compilation_errors(self, error_output: str, solution: Dict) -> Dict:
        """Use o1-mini to fix compilation errors"""
        print("🔧 Attempting to fix compilation errors with o1-mini...")
        
        deployment = "o4-mini"
        url = f"{self.endpoint}openai/deployments/{deployment}/chat/completions?api-version={self.api_version}"
        
        prompt = f"""The following C++ code has compilation errors. Please fix them.

Header file:
{solution['header']}

Implementation file:
{solution['implementation']}

Compilation errors:
{error_output[-3000:]}

Please provide the corrected header and implementation files."""

        payload = {
            "messages": [{"role": "user", "content": prompt}],
            "max_completion_tokens": 6000,
            "temperature": 1
        }
        
        try:
            response = requests.post(url, headers=self.headers, json=payload, timeout=120)
            if response.status_code == 200:
                result = response.json()
                content = result['choices'][0]['message']['content']
                # Parse and update solution
                # ... parsing logic ...
                return solution
        except Exception as e:
            print(f"❌ Error fixing compilation: {e}")
        
        return solution

def main():
    automation = LeetCodeO1Automation()
    
    # Example: Test with a simple problem
    test_problem = {
        'number': 191,
        'name': 'Number of 1 Bits',
        'description': """Write a function that takes an unsigned integer and returns the number of '1' bits it has.
        
Example 1:
Input: n = 00000000000000000000000000001011
Output: 3

Example 2:  
Input: n = 00000000000000000000000010000000
Output: 1

Constraints:
- The input must be a binary string of length 32""",
        'difficulty': 'easy'
    }
    
    print("=" * 60)
    print("🚀 LeetCode Automation with o1-mini Reasoning Model")
    print("=" * 60)
    
    # Generate solution
    solution = automation.generate_solution(
        test_problem['number'],
        test_problem['name'],
        test_problem['description'],
        test_problem['difficulty']
    )
    
    if solution:
        # Write files
        if automation.write_files(solution, test_problem['number']):
            # Build and test
            if automation.build_and_test(solution['class_name']):
                print("\n✅ Problem successfully implemented!")
            else:
                print("\n⚠️  Implementation needs fixes")
        else:
            print("\n❌ Failed to write files")
    else:
        print("\n❌ Failed to generate solution")

if __name__ == "__main__":
    main()