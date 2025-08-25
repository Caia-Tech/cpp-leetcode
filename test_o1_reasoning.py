#!/usr/bin/env python3
"""
Test Azure OpenAI o1 reasoning models (o4-mini)
"""

import os
import requests
import json
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

def test_o1_reasoning():
    """Test o1 reasoning models with proper parameters"""
    
    api_key = os.getenv('AZURE_OPENAI_KEY')
    endpoint = os.getenv('AZURE_OPENAI_ENDPOINT')
    api_version = "2024-12-01-preview"  # Required for o1 models
    
    print("Testing o1 Reasoning Models")
    print("=" * 60)
    print(f"Endpoint: {endpoint}")
    print(f"API Version: {api_version}")
    print("=" * 60)
    
    # Test o4-mini (o1-mini reasoning model)
    deployment_name = "o4-mini"
    
    print(f"\nTesting {deployment_name} (o1-mini reasoning model):")
    print("-" * 40)
    
    url = f"{endpoint}openai/deployments/{deployment_name}/chat/completions?api-version={api_version}"
    
    headers = {
        "api-key": api_key,
        "Content-Type": "application/json"
    }
    
    # o1 models use different parameters
    payload = {
        "messages": [
            {
                "role": "user",
                "content": """Solve this step by step: 
                
                Write a function to find the longest increasing subsequence in an array.
                Show your reasoning process and provide the optimal solution."""
            }
        ],
        "max_completion_tokens": 2000,  # Note: NOT max_tokens for o1 models
        "temperature": 1  # o1 models only support temperature=1
    }
    
    try:
        print("Sending request...")
        response = requests.post(url, headers=headers, json=payload, timeout=30)
        
        if response.status_code == 200:
            result = response.json()
            content = result['choices'][0]['message']['content']
            usage = result.get('usage', {})
            
            print(f"✅ Success! o1-mini reasoning model is working!")
            print(f"\n📊 Token Usage:")
            print(f"   Prompt tokens: {usage.get('prompt_tokens', 'N/A')}")
            print(f"   Completion tokens: {usage.get('completion_tokens', 'N/A')}")
            print(f"   Total tokens: {usage.get('total_tokens', 'N/A')}")
            
            # Check for reasoning tokens (unique to o1 models)
            if 'completion_tokens_details' in usage:
                details = usage['completion_tokens_details']
                if 'reasoning_tokens' in details:
                    print(f"   🧠 Reasoning tokens: {details['reasoning_tokens']}")
            
            print(f"\n📝 Response (first 500 chars):")
            print("-" * 40)
            print(content[:500] + "..." if len(content) > 500 else content)
            
            # Get model details
            if 'model' in result:
                print(f"\n📌 Model: {result['model']}")
                
        else:
            print(f"❌ Failed: {response.status_code}")
            error_detail = response.json() if response.text else response.text
            print(f"   Error: {json.dumps(error_detail, indent=2)}")
            
    except Exception as e:
        print(f"❌ Exception: {e}")
    
    print("\n" + "=" * 60)
    print("🎯 Key Differences for o1 Models:")
    print("-" * 40)
    print("1. Use 'max_completion_tokens' instead of 'max_tokens'")
    print("2. Temperature must be 1 (no variation allowed)")
    print("3. No system messages allowed (user messages only)")
    print("4. Includes 'reasoning_tokens' in usage for chain-of-thought")
    print("5. Better at complex reasoning and step-by-step problem solving")
    print("\n💡 Perfect for LeetCode hard problems that need deep reasoning!")

if __name__ == "__main__":
    test_o1_reasoning()