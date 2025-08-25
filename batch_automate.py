#!/usr/bin/env python3
"""
Batch automation for LeetCode problems using o1-mini
Processes multiple problems from PROBLEM_TRACKER.md
"""

import os
import re
import time
import json
from pathlib import Path
from typing import List, Dict
from automate_leetcode_o1 import LeetCodeO1Automation

class BatchLeetCodeProcessor:
    def __init__(self):
        self.automation = LeetCodeO1Automation()
        self.problems_file = Path("PROBLEM_TRACKER.md")
        self.completed_count = 0
        self.failed_problems = []
        
    def parse_problem_tracker(self) -> List[Dict]:
        """Parse PROBLEM_TRACKER.md to find pending problems"""
        content = self.problems_file.read_text()
        
        # Find all unchecked problems in the Next Batch sections
        pending_problems = []
        
        # Pattern to match unchecked problems: - [ ] NUMBER. Name
        pattern = r'- \[ \] (\d+)\. (.+?)(?:\n|$)'
        matches = re.findall(pattern, content)
        
        for number, name in matches:
            # Determine difficulty based on section
            # This is simplified - you'd parse sections properly
            difficulty = 'easy'  # Default, would need proper section parsing
            
            pending_problems.append({
                'number': int(number),
                'name': name.strip(),
                'difficulty': difficulty,
                'description': ''  # Would need to fetch from LeetCode or API
            })
        
        return pending_problems
    
    def get_problem_description(self, problem_number: int, problem_name: str) -> str:
        """
        Get problem description. In production, this would:
        1. Check local cache
        2. Fetch from LeetCode API if available
        3. Use web scraping as fallback
        """
        # For now, return a placeholder
        return f"""
        [Problem {problem_number}: {problem_name}]
        
        This is where the full problem description would go.
        In production, this would be fetched from:
        - Local problem cache
        - LeetCode API
        - Web scraping
        """
    
    def update_problem_tracker(self, problem: Dict, success: bool):
        """Update PROBLEM_TRACKER.md to mark problem as completed"""
        if not success:
            return
            
        content = self.problems_file.read_text()
        
        # Change - [ ] to - [x] for this problem
        old_pattern = f"- \\[ \\] {problem['number']}\\. {problem['name']}"
        new_pattern = f"- [x] {problem['number']}. {problem['name']}"
        
        content = re.sub(old_pattern, new_pattern, content)
        
        # Update counts
        content = re.sub(
            r'✅ Implemented \((\d+) problems\)',
            lambda m: f"✅ Implemented ({int(m.group(1)) + 1} problems)",
            content
        )
        
        # Update difficulty count
        if problem['difficulty'] == 'easy':
            content = re.sub(
                r'\*\*Easy\*\*: (\d+)/~800',
                lambda m: f"**Easy**: {int(m.group(1)) + 1}/~800",
                content
            )
        
        self.problems_file.write_text(content)
        print(f"✅ Updated PROBLEM_TRACKER.md")
    
    def process_problem(self, problem: Dict) -> bool:
        """Process a single problem"""
        print("\n" + "=" * 60)
        print(f"📝 Processing Problem {problem['number']}: {problem['name']}")
        print("=" * 60)
        
        # Get full description
        if not problem['description']:
            problem['description'] = self.get_problem_description(
                problem['number'], 
                problem['name']
            )
        
        # Generate solution
        solution = self.automation.generate_solution(
            problem['number'],
            problem['name'],
            problem['description'],
            problem['difficulty']
        )
        
        if not solution:
            print(f"❌ Failed to generate solution")
            self.failed_problems.append(problem)
            return False
        
        # Write files
        if not self.automation.write_files(solution, problem['number']):
            print(f"❌ Failed to write files")
            self.failed_problems.append(problem)
            return False
        
        # Build and test
        success = self.automation.build_and_test(solution['class_name'])
        
        if success:
            self.completed_count += 1
            self.update_problem_tracker(problem, True)
            
            # Commit changes
            self.git_commit(f"Add Problem {problem['number']}: {problem['name']}")
        else:
            self.failed_problems.append(problem)
        
        return success
    
    def git_commit(self, message: str):
        """Commit and push changes"""
        import subprocess
        
        try:
            subprocess.run(["git", "add", "-A"], check=True)
            subprocess.run(["git", "commit", "-m", message], check=True)
            subprocess.run(["git", "push"], check=True)
            print(f"✅ Committed and pushed: {message}")
        except subprocess.CalledProcessError as e:
            print(f"⚠️  Git operation failed: {e}")
    
    def run_batch(self, max_problems: int = 5, difficulty_filter: str = None):
        """Process a batch of problems"""
        print("🚀 Starting Batch LeetCode Automation")
        print(f"   Max problems: {max_problems}")
        print(f"   Difficulty filter: {difficulty_filter or 'all'}")
        
        # Get pending problems
        pending = self.parse_problem_tracker()
        
        # Filter by difficulty if specified
        if difficulty_filter:
            pending = [p for p in pending if p['difficulty'] == difficulty_filter]
        
        print(f"\n📊 Found {len(pending)} pending problems")
        
        # Process batch
        for i, problem in enumerate(pending[:max_problems]):
            print(f"\n[{i+1}/{min(max_problems, len(pending))}] Processing...")
            
            success = self.process_problem(problem)
            
            # Rate limiting
            if i < max_problems - 1:
                wait_time = 30 if success else 10
                print(f"⏱️  Waiting {wait_time} seconds before next problem...")
                time.sleep(wait_time)
        
        # Summary
        print("\n" + "=" * 60)
        print("📊 Batch Processing Summary")
        print("=" * 60)
        print(f"✅ Successfully completed: {self.completed_count}")
        print(f"❌ Failed: {len(self.failed_problems)}")
        
        if self.failed_problems:
            print("\nFailed problems:")
            for p in self.failed_problems:
                print(f"  - {p['number']}. {p['name']}")
        
        return self.completed_count

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='Batch process LeetCode problems')
    parser.add_argument('--count', type=int, default=5, help='Number of problems to process')
    parser.add_argument('--difficulty', choices=['easy', 'medium', 'hard'], 
                       help='Filter by difficulty')
    parser.add_argument('--start-from', type=int, help='Start from specific problem number')
    
    args = parser.parse_args()
    
    processor = BatchLeetCodeProcessor()
    completed = processor.run_batch(args.count, args.difficulty)
    
    print(f"\n✨ Batch processing complete! Added {completed} problems.")

if __name__ == "__main__":
    main()